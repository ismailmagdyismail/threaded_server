#!/bin/bash

export working_dir=$PWD

export src_dir=src
export src_path=$working_dir/$src_dir

export build_dir=build
export build_path=$working_dir/$build_dir

export bin_dir=bin
export bin_path=$working_dir/$bin_dir

export build_type=debug

export SERVER_PORT_NUMBER=8080


function build_lib()
{
  create_artifacts_dir
  cmake -S $src_path/lib -B $build_path/lib -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=$build_type
  cmake --build $build_dir/lib --parallel
}

function build_server()
{
  create_artifacts_dir
  cmake -S $src_path/server -B $build_path/server -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=$build_type
  cmake --build $build_dir/server --parallel
}

function build_client()
{
  create_artifacts_dir
  cmake -S $src_path/client -B $build_path/client -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=$build_type
  cmake --build $build_dir/client --parallel
}

function build()
{
  build_lib
  build_server
  build_client
}

function build_run()
{
  build
  run
}


function run() {
  echo "1- CLIENT"
  echo "2- SERVER"
  
  # read -p "Enter process you need to run: " choice
  echo -n "Enter process you need to run: " 
  read choice 
  case $choice in
    1)
      echo "Running CLIENT..."
      $bin_dir/CLIENT
      ;;
    2)
      echo "Running SERVER..."
      $bin_dir/SERVER
      ;;
    *)
      echo "Invalid Choice!"
      ;;
  esac
}

function create_artifacts_dir()
{
  mkdir -p $build_path  
  mkdir -p $bin_path
}

function CLEAN()
{
  rm -rf "${build_dir}"
  rm -rf "${bin_dir}"
}
create_artifacts_dir
