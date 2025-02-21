export working_dir=$PWD

export src_dir=src
export src_path=$working_dir/$src_dir

export build_dir=build
export build_path=$working_dir/$build_dir

export bin_dir=bin
export bin_path=$working_dir/$bin_dir

export build_type=debug

function build()
{
  cmake -B $build_path 
  cmake --build $build_dir --config $build_type --parallel
}

function build_run()
{ 
  build
  run
}

function run()
{
  if [[ ! -f $bin_path/WEB_SERVER ]]; then
    echo "Not compiled yet"
    return;
  fi 
  $bin_path/WEB_SERVER
}

function create_artifacts_dir()
{
  mkdir -p $build_path  
  mkdir -p $bin_path
}

create_artifacts_dir
