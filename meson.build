project(
    'openpower-debug-collector',
    'cpp',
    meson_version: '>= 0.57.0',
    default_options: [
        'warning_level=3',
        'werror=true',
        'cpp_std=c++20'
    ],
    license: 'Apache-2.0',
    version: '1.0.0',
)

systemd = dependency('systemd', required : true)

sdbusplus = dependency(
    'sdbusplus',
    fallback: [
        'sdbusplus',
        'sdbusplus_dep'
    ]
)
sdbusplusplus_prog = find_program('sdbus++', required : true)
sdbuspp_gen_meson_prog = find_program('sdbus++-gen-meson', required : true)

phosphorlogging = dependency(
    'phosphor-logging',
    fallback: [
        'phosphor-logging',
        'phosphor_logging_dep'
    ]
)

deps = [
    systemd, sdbusplus, phosphorlogging
]

realpath_prog = find_program('realpath')

selected_subdirs = []
selected_subdirs += 'org/open_power'

generated_root = meson.current_build_dir() / 'gen'
generated_others = []
generated_sources = []

# Source the generated meson files
subdir('gen')
foreach d : selected_subdirs
    subdir('gen' / d)
endforeach

# Parse through the list from sdbus++-gendir and put into sets.
generated_headers = []
generated_cpp = []
generated_others_files = []

foreach g : generated_sources generated_others
    foreach f : g.to_list()
        rel_path = run_command(
            realpath_prog,
            '--relative-to', generated_root,
            f.full_path(),
        ).stdout().strip().split('\n')[-1]

        if rel_path.endswith('.hpp')
            generated_headers += rel_path
        elif rel_path.endswith('.cpp')
            generated_cpp += rel_path
        else
            generated_others_files += rel_path
        endif
    endforeach
endforeach

executable('watchdog_timeout',
    'watchdog_timeout.cpp',
    generated_sources,
    dependencies: deps,
    include_directories: include_directories('gen'),
    implicit_include_directories: true,
    install: true
)

executable('checkstop_app',
    'checkstop_app.cpp',
    generated_sources,
    dependencies: deps,
    include_directories: include_directories('gen'),
    implicit_include_directories: true,
    install: true
)
