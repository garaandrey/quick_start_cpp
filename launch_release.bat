@echo off
chcp 65001
setlocal EnableDelayedExpansion
set app=bin\quick_start_cpp_x64.exe

start ""  "%app%"  -video_app auto -video_vsync 0 -video_refresh 0 -video_mode 1 -video_resizable 1 -video_fullscreen 0 -video_debug 0 -sound_app auto -data_path "../data/" -extern_plugin "FbxImporter,GLTFImporter,FbxExporter" -console_command "config_autosave 0 && world_load \"quick_start_cpp\""
