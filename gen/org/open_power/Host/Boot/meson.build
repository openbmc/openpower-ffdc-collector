# Generated file; do not modify.
generated_sources += custom_target(
    'org/open_power/Host/Boot__cpp'.underscorify(),
    input: [ meson.project_source_root() / 'org/open_power/Host/Boot.errors.yaml',  ],
    output: [ 'error.cpp', 'error.hpp',  ],
    command: [
        sdbuspp_gen_meson_prog, '--command', 'cpp',
        '--output', meson.current_build_dir(),
        '--tool', sdbusplusplus_prog,
        '--directory', meson.project_source_root(),
        'org/open_power/Host/Boot',
    ],
)

