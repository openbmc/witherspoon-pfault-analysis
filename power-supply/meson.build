librecord_manager = static_library(
    'record_manager',
    'record_manager.cpp',
    dependencies: [
        phosphor_logging,
    ],
)

executable(
    'psu-monitor',
    'argument.cpp',
    error_hpp,
    'main.cpp',
    'power_supply.cpp',
    dependencies: [
        phosphor_dbus_interfaces,
        phosphor_logging,
        sdbusplus,
    ],
    include_directories: '..',
    install: true,
    link_with: [
        libpower,
        librecord_manager,
    ]
)

subdir('test')
