# Custom Memory Management System

## Overview

This project implements a custom memory management system in C++ designed for performance and efficiency. The system uses a combination of free and used node management to optimize memory allocation and deallocation, which is critical in high-performance applications.

## Performance Highlights

* **Optimized Memory Management**: The custom memory allocator significantly reduces fragmentation and improves allocation speed.
* **Speed Improvement**: Benchmarks show that this implementation runs on average **1.8 times faster** than conventional memory management techniques on a **Ryzen 9 5900HX** laptop, demonstrating the effectiveness of the custom approach.

## Key Features

* **Efficient Allocation**: The memory system is built to allocate memory blocks quickly and efficiently, leveraging a next-fit strategy that minimizes search time for free blocks.
* **Coalescing**: It automatically merges adjacent free blocks upon deallocation to reduce fragmentation and maximize usable memory space.
* **Robustness**: The system includes thorough assertions to ensure the integrity of memory operations, reducing the likelihood of runtime errors.

## Conclusion

This project showcases advanced C++ techniques, including custom memory management, pointers, and dynamic memory operations, highlighting my proficiency in the language and my ability to implement high-performance systems.
