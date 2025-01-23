
#include "../core.hpp"

auto client::core::ipc::initialize(unsigned __int64 address) -> __int32
{
	if (address == 0)
		REPORT_EXIT_RETURN(1);

	auto module_nt_headers = (_IMAGE_NT_HEADERS64*)(address + (unsigned __int64)((_IMAGE_DOS_HEADER*)address)->e_lfanew);

	auto module_export_directory = (_IMAGE_EXPORT_DIRECTORY*)(address + (unsigned __int64)module_nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);

	auto module_export_directory_functions = (unsigned __int32*)(address + (unsigned __int64)module_export_directory->AddressOfFunctions);

	auto module_export_directory_names = (unsigned __int32*)(address + (unsigned __int64)module_export_directory->AddressOfNames);

	auto module_export_directory_ordinals = (unsigned __int16*)(address + (unsigned __int64)module_export_directory->AddressOfNameOrdinals);

	auto module_export_directory_size = module_nt_headers->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;

	for (unsigned __int32 x = 0; x < module_export_directory->NumberOfNames; ++x)
	{
		auto module_export_name = sdk::__multibyte_string((char*)(address + module_export_directory_names[x]));

		if (!sdk::__multibyte_string::is_valid(module_export_name))
			REPORT_EXIT_RETURN(1);

		auto fix_module_export_name = [](sdk::__multibyte_string module_export_name) -> sdk::__multibyte_string
		{
			if (!sdk::__multibyte_string::is_valid(module_export_name))
				REPORT_EXIT_RETURN(nullptr);

			auto fixed_module_export_name = sdk::__multibyte_string();

			module_export_name.left_pop();

			module_export_name.get_multibyte_string()[module_export_name.left_find(XOR("@@")) + 1] = 0;

			auto namespaces = std::vector<sdk::__multibyte_string>();

			for (unsigned __int64 x = 0; x < module_export_name.get_length(); ++x)
			{
				static auto temporal_namespace = sdk::__multibyte_string();

				if (module_export_name.get_multibyte_string()[x] == '@')
				{
					namespaces.push_back(temporal_namespace);

					temporal_namespace = XOR("");

					continue;
				}

				temporal_namespace.concatenate(sdk::__multibyte_string(&module_export_name.get_multibyte_string()[x], 1).get_multibyte_string());
			}

			std::reverse(namespaces.begin(), namespaces.end());

			for (auto& temporal_namespace : namespaces)
				fixed_module_export_name.concatenate(temporal_namespace.get_multibyte_string(), XOR("::"));

			fixed_module_export_name.right_pop();
			fixed_module_export_name.right_pop();

			return fixed_module_export_name;
		};

		auto fixed_module_export_name = fix_module_export_name(module_export_name);

		if (!sdk::__multibyte_string::is_valid(fixed_module_export_name))
			EXTRA_REPORT_EXIT_RETURN(module_export_name, 1);

		auto module_export_address = address + module_export_directory_functions[module_export_directory_ordinals[x]];

		if (module_export_address == 0)
			EXTRA_REPORT_EXIT_RETURN(fixed_module_export_name, 1);

		client::core::ipc::settings.push_back({ fixed_module_export_name, module_export_address });
	}

	client::core::ipc::uninitialized = true;

	return 0;
}

auto client::core::ipc::get_setting_address(sdk::__multibyte_string name) -> unsigned __int64
{
	unsigned __int64 setting_address = 0;

	if (!sdk::__multibyte_string::is_valid(name))
		REPORT_EXIT_RETURN(0);

	for (auto setting : client::core::ipc::settings)
	{
		if (setting.first.equals(name.get_multibyte_string()))
		{
			if (setting_address != 0)
				EXTRA_REPORT_EXIT_RETURN(name, 0);

			setting_address = setting.second;
		}
	}

	if (setting_address == 0)
		EXTRA_REPORT_EXIT_RETURN(name, 0);

	return setting_address;
}