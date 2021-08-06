// Protocol Buffers - Google's data interchange format
// Copyright 2008 Google Inc.  All rights reserved.
// https://developers.google.com/protocol-buffers/
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// Author: petar@google.com (Petar Petrov)

#ifndef GOOGLE_PROTOBUF_PYTHON_CPP_DESCRIPTOR_H__
#define GOOGLE_PROTOBUF_PYTHON_CPP_DESCRIPTOR_H__

#include <Python.h>

#include <google/protobuf/descriptor.h>

namespace google {
namespace protobuf {
namespace python {

extern PyTypeObject PyMessageDescriptor_Type;
extern PyTypeObject PyFieldDescriptor_Type;
extern PyTypeObject PyEnumDescriptor_Type;
extern PyTypeObject PyEnumValueDescriptor_Type;
extern PyTypeObject PyFileDescriptor_Type;
extern PyTypeObject PyOneofDescriptor_Type;
extern PyTypeObject PyServiceDescriptor_Type;
extern PyTypeObject PyMethodDescriptor_Type;

// Wraps a Descriptor in a Python object.
// The C++ pointer is usually borrowed from the global DescriptorPool.
// In any case, it must stay alive as long as the Python object.
// Returns a new reference.
PyObject* PyMessageDescriptor_FromDescriptor(const Descriptor* descriptor);
PyObject* PyFieldDescriptor_FromDescriptor(const FieldDescriptor* descriptor);
PyObject* PyEnumDescriptor_FromDescriptor(const EnumDescriptor* descriptor);
PyObject* PyEnumValueDescriptor_FromDescriptor(
    const EnumValueDescriptor* descriptor);
PyObject* PyOneofDescriptor_FromDescriptor(const OneofDescriptor* descriptor);
PyObject* PyFileDescriptor_FromDescriptor(
    const FileDescriptor* file_descriptor);
PyObject* PyServiceDescriptor_FromDescriptor(
    const ServiceDescriptor* descriptor);
PyObject* PyMethodDescriptor_FromDescriptor(
    const MethodDescriptor* descriptor);

// Alternate constructor of PyFileDescriptor, used when we already have a
// serialized FileDescriptorProto that can be cached.
// Returns a new reference.
PyObject* PyFileDescriptor_FromDescriptorWithSerializedPb(
    const FileDescriptor* file_descriptor, PyObject* serialized_pb);

// Return the C++ descriptor pointer.
// This function checks the parameter type; on error, return NULL with a Python
// exception set.
const Descriptor* PyMessageDescriptor_AsDescriptor(PyObject* obj);
const FieldDescriptor* PyFieldDescriptor_AsDescriptor(PyObject* obj);
const EnumDescriptor* PyEnumDescriptor_AsDescriptor(PyObject* obj);
const FileDescriptor* PyFileDescriptor_AsDescriptor(PyObject* obj);

// Returns the raw C++ pointer.
const void* PyDescriptor_AsVoidPtr(PyObject* obj);

// Check that the calling Python code is the global scope of a _pb2.py module.
// This function is used to support the current code generated by the proto
// compiler, which insists on modifying descriptors after they have been
// created.
//
// stacklevel indicates which Python frame should be the _pb2.py module.
//
// Don't use this function outside descriptor classes.
bool _CalledFromGeneratedFile(int stacklevel);

bool InitDescriptor();

}  // namespace python
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_PYTHON_CPP_DESCRIPTOR_H__
