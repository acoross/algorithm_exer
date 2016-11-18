cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
# Above line indicates to Cmake that minimum version 2.8 is required.
# As you may have noted all lines beginning with hash symbol are treated as comments by Cmake.
SET(sampleName MyApp)
# In the above line we declared a variable sampleName and assigned it a value MyApp. We will make use of the same later.project(PrjMyApp)
# here we define the project or solution (for visual studio) name

# The following line is very important.
# It specifies the executable name. Here the executable is the first parameter i.e. MyApp and a file MyApp.exe will be created on
# compilation in windows platform.
# Followed by the executable name come all your source and header files.
# All cpp fles will be clubbed into source folder and all .h files will be added to header files folder of the project.
add_executable (MyApp avl.cpp avl.hpp avl_tree.cpp avl_tree.hpp binary_tree.cpp binary_tree.hpp binary_tree_node.hpp bst.cpp bst.hpp coding_dojang.cpp coding_dojang.hpp count_num_under_1000.cpp count_num_under_1000.hpp crack_interview_ch1.cpp crack_interview_ch1.hpp crack_interview_ch2.cpp crack_interview_ch2.hpp crack_interview_ch3.cpp crack_interview_ch3.hpp crack_interview_ch4.cpp crack_interview_ch4.hpp crack_interview_ch5.cpp crack_interview_ch5.hpp crack_interview_ch9.cpp crack_interview_ch9.hpp main.cpp red_black_tree.hpp sort.cpp sort.hpp)

# End of CMakeLists.Txt file. Save it as a plain text file and the name should be exactly CMakeLists.Txt