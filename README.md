# Octree-based Image Compression

## Overview
This project aims to implement an octree data structure in the C language to reduce the number of different color pixels in an image, thereby compressing its size. By utilizing the octree structure, the program identifies and groups similar color pixels together, effectively reducing redundancy and optimizing image storage.

## Features
- **Octree Data Structure:** Utilizes an octree to organize and analyze color pixel data efficiently.
- **Image Compression:** Reduces the number of distinct color pixels in an image, resulting in smaller file sizes.
- **Customization:** Users can adjust compression settings to achieve desired levels of image quality and file size reduction.

## How it Works
1. **Image Input:** The program takes an input image file in a common format such as JPEG or PNG.
2. **Color Analysis:** It analyzes the color distribution in the image and constructs an octree data structure to represent this distribution.
3. **Compression:** By traversing the octree, the program identifies clusters of similar color pixels and replaces them with a single representative color.
4. **Output:** The compressed image is generated, with a reduced number of distinct color pixels, resulting in a smaller file size.

## Usage
1. Compile the program using a C compiler such as GCC.
2. Run the compiled executable, providing the input image file as an argument.
3. Optionally, adjust compression settings or specify output file parameters.
4. View the compressed image output.

Example:
```bash
$ gcc octree_image_compression.c -o octree_image_compression
$ ./octree_image_compression input_image.jpg
