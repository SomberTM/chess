mkdir -p build
cd build
cmake .. -DBUILD_TESTS=ON
cmake --build .

if [ -z "$1" ]; then
  echo "Running all tests in ./tests..."
  for test_exec in ./tests/*_test; do
    if [ -x "$test_exec" ]; then
      echo "Running: $test_exec"
      "$test_exec"
    fi
  done
else
  ./tests/"$1"_test
fi
