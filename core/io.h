#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef  struct {
	char* data; 
	size_t size; 
	bool inValid; 
} File;

File IoiceCreamReadFile(const char* filePath); 
int IoiceCreamWriteFile(void* buffer, size_t data, const char* filePath); 
