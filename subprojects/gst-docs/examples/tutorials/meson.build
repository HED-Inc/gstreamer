tutorial_dependencies = {
  'basic-tutorial-1': [dependency('gstreamer-1.0')],
  'basic-tutorial-2': [dependency('gstreamer-1.0')],
  'basic-tutorial-3': [dependency('gstreamer-1.0')],
  'basic-tutorial-4': [dependency('gstreamer-1.0')],
  'basic-tutorial-5': [dependency('gstreamer-1.0'), dependency('gtk+-3.0'), dependency('gstreamer-video-1.0')],
  'basic-tutorial-6': [dependency('gstreamer-1.0')],
  'basic-tutorial-7': [dependency('gstreamer-1.0')],
  'basic-tutorial-8': [dependency('gstreamer-1.0'), dependency('gstreamer-audio-1.0')],
  'basic-tutorial-9': [dependency('gstreamer-1.0'), dependency('gstreamer-pbutils-1.0')],
  'basic-tutorial-12': [dependency('gstreamer-1.0')],
  'basic-tutorial-13': [dependency('gstreamer-1.0')],
  'basic-tutorial-15': [dependency('clutter-gst-3.0', required: false)],
  'playback-tutorial-1': [dependency('gstreamer-1.0')],
  'playback-tutorial-2': [dependency('gstreamer-1.0')],
  'playback-tutorial-3': [dependency('gstreamer-1.0'), dependency('gstreamer-audio-1.0')],
  'playback-tutorial-4': [dependency('gstreamer-1.0')],
  'playback-tutorial-5': [dependency('gstreamer-1.0'), dependency('gstreamer-video-1.0')],
  'playback-tutorial-6': [dependency('gstreamer-1.0')],
  'playback-tutorial-7': [dependency('gstreamer-1.0')]
}

clutter_gst_dep = dependency('clutter-gst-3.0', required: false) #Aims to find clutter dependency

# Iterate over all tutorials and create an executable for each
foreach tutorial, deps : tutorial_dependencies

  has_clutter = false
  foreach dep : deps
    if dep.name() == 'clutter-gst-3.0'
      has_clutter = true
    endif
  endforeach

  if has_clutter and not clutter_gst_dep.found()
    message('Skipping @0@ because clutter-gst-3.0 is not available.'.format(tutorial))
  else
    executable(tutorial, '@0@.c'.format(tutorial), dependencies : deps)
  endif
endforeach
