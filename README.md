# ft_containers

In this project, I implemented a few container types of the C++ standard template library

[Vector](https://en.cppreference.com/w/cpp/container/vector)

[Map](https://en.cppreference.com/w/cpp/container/map)

[Set](https://en.cppreference.com/w/cpp/container/set)

[Stack](https://en.cppreference.com/w/cpp/container/stack)

Set and Map search, removal, and insertion operations have logarithmic complexity and implemented as [Red–black tree](https://en.wikipedia.org/wiki/Red%E2%80%93black_tree), which is kind of self-balancing binary search tree.
![img](https://user-images.githubusercontent.com/37631996/204149607-da89f88c-56cc-4b61-a163-3c828ccad4ad.gif)

Tree implemntation, iterators and couple of supporting functions(pair, enable_if and etc.) was implemented.
Memory allocation was perfomed by [std::allocator](https://en.cppreference.com/w/cpp/memory/allocator)



Tester is included. To run it:
cd into the folder 'container_test'
run command 'bash do.sh'

Test result
![img](https://user-images.githubusercontent.com/37631996/204149467-a881f775-b3f2-40dd-8dab-aa6358d8fed7.png)

