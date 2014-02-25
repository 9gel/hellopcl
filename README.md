Point Cloud Library Sample for XCode 5
======================================

This is a complete XCode project for running the [Point Cloud Library](http://pointclouds.org/) in XCode 5. My intention is to get to a running app as quickly as possible.

To run, clone this repository and do the following:

- Install boost and have the headers available in `/usr/local/include`. I use Homebrew: `brew install boost`
- unzip the framework binaries (they are zipped to get around the 100Mb file limitation of github):
 - `frameworks/pcl.framework/pcl.zip -> frameworks/pcl.framework/pcl`
 - `frameworks/vtk.framework/vtk.zip -> frameworks/vtk.framework/vtk`

Open HelloPCL.xcodeproj in XCode 5. Choose "iOS Device" or the name of your attached device as target, then Compile or Run it.

Background
----------

I tried to follow the instructions [here](http://www.vtk.org/Wiki/VES/Point_Cloud_Library) in the VTK wiki to get a PCL iOS Example App running. There were some issues trying to build from source in that particular branch. Fortunately Kitware provided pre-built [vtk, pcl and kiwi frameworks](http://packages.kitware.com/packages/application/view?applicationId=14) for download. I re-constructed an XCode project from the files and using the frameworks. Here are some of thing things I did to make it work:

- Create a new XCode project with one view
- Added all necessary frameworks including the three from Kitware
- Added all files from the example code HelloPCL. That includes all .h, .m, .cxx and nib files.
- Adjusted #include in the source files, both in the framework and the example code
- Set architecture to armv7 only because the pcl framework was only available for that architecture
- Set C++ dialect to GNU++98
- Set C++ standard library to libstdc++
- Set Compile sources as Objective-C++

I was able to run this on my iPad Mini Retina and my iPad 3rd gen (Retina).

More: the specific download links of the framework files:
- [vtk](http://packages.kitware.com/download?items=3016)
- [pcl](http://packages.kitware.com/download?items=3017)
- [kiwi](http://packages.kitware.com/download?items=3015)
