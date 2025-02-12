import subprocess

# Step 1: Compile the C++ file
compile_command = ["g++", "C:/Users/fabia/VSCODE_projects/HPP/BucketSortV2/BucketSortV2/src/main.cpp", "-o", "my_cpp_program"]
compile_result = subprocess.run(compile_command, capture_output=True, text=True)

if compile_result.returncode != 0:
    print("Compilation failed!")
    print(compile_result.stderr)  # Show the error message
else:
    print("Compilation successful!")

    # Step 2: Run the compiled executable
    run_command = ["./example"]
    run_result = subprocess.run(run_command, capture_output=True, text=True)

    if run_result.returncode == 0:
        print("Program output:")
        print(run_result.stdout)  # Show the program's output
    else:
        print("Program failed to run!")
        print(run_result.stderr)  # Show the error message
