#include "Buffer.h"

#include <iostream>

Buffer::Buffer(const float* vertices, size_t vertexSize, const GLuint* indices, size_t indexSize) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexSize, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, indices, GL_STATIC_DRAW);
}

Buffer::~Buffer() {

}

void Buffer::bind() {
    glBindVertexArray(VAO);
}

void Buffer::unbind() {
    glBindVertexArray(0);
}

void Buffer::addLayout(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset) {
    glVertexAttribPointer(index, size, type, normalized, stride, offset);
    glEnableVertexAttribArray(index);
}