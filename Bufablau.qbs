import qbs
import qbs.Process
import qbs.File
import qbs.FileInfo
import qbs.TextFile
import "/home/anna/Dropbox/_Anna/OF/of_v0.10.1_linux64gcc5_release/libs/openFrameworksCompiled/project/qtcreator/ofApp.qbs" as ofApp

Project{
    property string of_root: '/home/anna/Dropbox/_Anna/OF/of_v0.10.1_linux64gcc5_release'

    ofApp {
        name: { return FileInfo.baseName(sourceDirectory) }

        files: [
            'src/main.cpp',
            'src/ofApp.cpp',
            'src/ofApp.h',
            'src/em/ofxINAbstract.h',
            'src/em/ofxINObject.h',
            'src/em/ofxINObject.cpp',
            'src/em/util/ofxINInterpolator.h',
            'src/em/util/ofxINInterpolator.cpp',
            'src/em/util/ofxINOscillator.h',
            'src/em/util/ofxINOscillator.cpp',
            'src/em/util/ofxINTimer.h',
            'src/em/util/ofxINTimer.cpp',
            'src/em/util/PennerEasing/Back.h',
            'src/em/util/PennerEasing/Back.cpp',
            'src/em/util/PennerEasing/Bounce.h',
            'src/em/util/PennerEasing/Bounce.cpp',
            'src/em/util/PennerEasing/Circ.h',
            'src/em/util/PennerEasing/Circ.cpp',
            'src/em/util/PennerEasing/Cubic.h',
            'src/em/util/PennerEasing/Cubic.cpp',
            'src/em/util/PennerEasing/Elastic.h',
            'src/em/util/PennerEasing/Elastic.cpp',
            'src/em/util/PennerEasing/Expo.h',
            'src/em/util/PennerEasing/Expo.cpp',
            'src/em/util/PennerEasing/Linear.h',
            'src/em/util/PennerEasing/Linear.cpp',
            'src/em/util/PennerEasing/Quad.h',
            'src/em/util/PennerEasing/Quad.cpp',
            'src/em/util/PennerEasing/Quart.h',
            'src/em/util/PennerEasing/Quart.cpp',
            'src/em/util/PennerEasing/Quint.h',
            'src/em/util/PennerEasing/Quint.cpp',
            'src/em/util/PennerEasing/Sine.h',
            'src/em/util/PennerEasing/Sine.cpp',
            'src/skin/VBat.hpp',
            'src/skin/VBat.cpp',
            'src/skin/VBot.hpp',
            'src/skin/VBot.cpp',
            'src/skin/VDark.hpp',
            'src/skin/VDark.cpp',
            'src/skin/VDoble.hpp',
            'src/skin/VDoble.cpp',
            'src/skin/VPride.hpp',
            'src/skin/VPride.cpp',
            'src/skin/VTree.hpp',
            'src/skin/VTree.cpp',
            'src/visual/Visual.hpp',
            'src/visual/Visual.cpp',
            'src/visual/VSObject.hpp',
            'src/visual/VSObject.cpp',
            'src/visual/objects/ParticleSystem.hpp',
            'src/visual/objects/ParticleSystem.cpp',
            'src/visual/objects/VBlobs.hpp',
            'src/visual/objects/VBlobs.cpp',
            'src/visual/objects/VStick.hpp',
            'src/visual/objects/VStick.cpp',
            'src/visual/objects/VUtils.h',
        ]

        of.addons: [
            'ofxGui',
            'ofxXmlSettings'
        ]

        // additional flags for the project. the of module sets some
        // flags by default to add the core libraries, search paths...
        // this flags can be augmented through the following properties:
        of.pkgConfigs: []       // list of additional system pkgs to include
        of.includePaths: []     // include search paths
        of.cFlags: []           // flags passed to the c compiler
        of.cxxFlags: []         // flags passed to the c++ compiler
        of.linkerFlags: []      // flags passed to the linker
        of.defines: []          // defines are passed as -D to the compiler
        // and can be checked with #ifdef or #if in the code
        of.frameworks: []       // osx only, additional frameworks to link with the project
        of.staticLibraries: []  // static libraries
        of.dynamicLibraries: [] // dynamic libraries

        // other flags can be set through the cpp module: http://doc.qt.io/qbs/cpp-module.html
        // eg: this will enable ccache when compiling
        //
        // cpp.compilerWrapper: 'ccache'

        Depends{
            name: "cpp"
        }

        // common rules that parse the include search paths, core libraries...
        Depends{
            name: "of"
        }

        // dependency with the OF library
        Depends{
            name: "openFrameworks"
        }
    }

    property bool makeOF: true  // use makfiles to compile the OF library
    // will compile OF only once for all your projects
    // otherwise compiled per project with qbs


    property bool precompileOfMain: false  // precompile ofMain.h
    // faster to recompile when including ofMain.h
    // but might use a lot of space per project

    references: [FileInfo.joinPaths(of_root, "/libs/openFrameworksCompiled/project/qtcreator/openFrameworks.qbs")]
}
