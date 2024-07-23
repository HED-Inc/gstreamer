find_module = files(
    'FindGStreamer.cmake',
)

installable_files = files(
    'gst_ios_init.m.in',
    'gstreamer_android-1.0.c.in',
)

install_data(
    find_module,
    install_dir: get_option('datadir') / 'cmake'
)

install_data(
    installable_files,
    install_dir: get_option('datadir') / 'cmake' / 'GStreamer'
)
