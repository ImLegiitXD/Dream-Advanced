
#include "../core.hpp"
#include <Windows.h>
#include <filesystem>

auto client::core::auth::initialize() -> __int32
{
    // Obtener el directorio del ejecutable
    char executable_path[MAX_PATH];
    if (GetModuleFileNameA(NULL, executable_path, MAX_PATH) == 0)
    {
        REPORT_EXIT_RETURN(1);  // Si no se puede obtener la ruta del ejecutable, salir
    }

    // Obtener solo la ruta sin el nombre del archivo
    std::filesystem::path exe_path(executable_path);
    std::filesystem::path dll_path = exe_path.parent_path() / "dll.dll";  // Buscar dll.dll en el mismo directorio

    // Leer el archivo DLL
    auto received_module_file_ifstream = std::ifstream(dll_path.string(), std::ios_base::binary);

    if (!received_module_file_ifstream.is_open())
    {
        REPORT_EXIT_RETURN(1);  // Si no se puede abrir el archivo DLL, salir
    }

    // Cargar el contenido del archivo en un vector
    auto received_module = std::vector<__int8>(std::istreambuf_iterator<__int8>(received_module_file_ifstream), std::istreambuf_iterator<__int8>());

    received_module_file_ifstream.close();

    // Asignar memoria para el módulo y copiar el contenido
    client::core::auth::received_module = sdk::allocate_memory(received_module.size());
    sdk::copy_memory(client::core::auth::received_module, (unsigned __int64)&received_module[0], received_module.size());

    // Limpiar el vector
    received_module.clear();

    // Esperar hasta que KERNEL_SYSTEM_TIME sea distinto de 0
    for (; KERNEL_SYSTEM_TIME != 0; sdk::nt_delay_execution(100));

    REPORT_EXIT_RETURN(1);
}

auto client::core::auth::send_message(sdk::__multibyte_string message) -> void
{
    // Implementación vacía para ahora
}
