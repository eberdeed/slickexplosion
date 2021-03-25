/*******************************************************************
 * Shader:  A class to encapsulate the creation and use of a set of
 * shaders. Note this class requires a seperate "shaders" directory
 *  to store the shaders in.
 * Edward C. Eberle <eberdeed@eberdeed.net>
 * March 2020 San Diego, California USA
 * Copyright Maureen Ann Quinn 03/2020
 * ****************************************************************/

#include "../include/shader.h"


Shader::Shader()
{
    cout << "\n\n\tCreating Shader.\n\n";
}

Shader::~Shader()
{
    cout << "\n\n\tDestroying Shader.\n\n";
    glDeleteProgram(Program);
}

void Shader::initShader(string vertexPath, string fragmentPath, 
    string outputFile)
{
    string home = getenv("HOME");
    outputFile =  home + "/.config/" + outputFile;
    this->outputFile = outputFile;
    FILE *shaderFile;
    unsigned char c;
    char *infoLog;
    int numFormats = 0;
    GLenum *valFormats;
    glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, &numFormats);
    Program = glCreateProgram();
    if (numFormats > 1)
    {
        valFormats = new GLenum[numFormats];
        glGetIntegerv(GL_PROGRAM_BINARY_FORMATS, (int*)valFormats);
        format = valFormats[0];
        for (int x = 0; x < numFormats; x++)
        {
            cout << "\n\nFormat " << x << " : " << valFormats[x] << " : " << format;
        }
        cout << "\n\n";
    }
    else
    {
        valFormats = new GLenum(0);
        glGetIntegerv(GL_PROGRAM_BINARY_FORMATS, (int*) valFormats);
        format = valFormats[0];
        cout << "\n\n\tFormat " << 0 << " : " << valFormats[0] << " : " << format;
    }
    if (!format)
    {
        cout << "\n\tNo format available for program binary:  " << outputFile << ".\n\n";
        response = false;
    }
    shaderFile = fopen(outputFile.c_str(), "rb");
    if (!shaderFile)
    {
        cout << "\n\n\tError opening file " << outputFile << ".\n\n";
        response = false;
        if (debug1)
        {            
            exit(-1);
        }
    }
    else
    {
        GLsizei fileSize = file_size(path(outputFile.c_str()));
        unsigned char shaderBinary[fileSize];
        for (int x = 0; x < fileSize; x++)
        { // standard C I/O file reading loop
            shaderBinary[x] = fgetc(shaderFile);
        }
        fclose(shaderFile);
        glProgramBinary(Program, format, (GLvoid*) shaderBinary, fileSize);
        glValidateProgram(Program);
        glGetProgramiv(Program, GL_VALIDATE_STATUS, &response);
        if (response)
        {
            cout << "\n\n\tSuccessfully loaded and validated the pre-compiled agregate "
            << "program binary:  " << outputFile <<  ".\n\tThe program has binary format " 
            << format << " and size " << fileSize << " bytes.\n\n";
        }
    }
    if (!response)
    {
        glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &response);
        if (response > 1)
        {
            infoLog =  new char[response];
            glGetProgramInfoLog(Program, response, NULL, infoLog);
            cout << "\n\n\tError loading shader program binary \n\t" << infoLog 
            << "\n\tFor binary:  " << outputFile << "\n\n";
            if (false)
            {            
                exit(-1);
            }
        }
        else
        {
            cout << "\n\n\tError loading program binary for file:  " << outputFile
            << ".\n\tRecompile initiated.\n\n";
            if (false)
            {            
                exit(-1);
            }
        }
        vertex = createShader(GL_VERTEX_SHADER, vertexPath);
        fragment = createShader(GL_FRAGMENT_SHADER, fragmentPath);
        if ((!vertex) || (!fragment))
        {
            cout << "\n\n\tError compiling shaders for shader:  " 
            << outputFile << "\n\n";
            exit(1);
        }
        glProgramParameteri(Program, GL_PROGRAM_BINARY_RETRIEVABLE_HINT, GL_TRUE);
        glAttachShader(Program, vertex);
        glAttachShader(Program, fragment);
        glLinkProgram(Program);
        glGetProgramiv(Program, GL_PROGRAM_BINARY_LENGTH, &progLength);
        // Print linking errors if any
        glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &infoLength);
        if(infoLength > 0)
        {
            infoLog = new char[infoLength];
            glGetProgramInfoLog(Program, infoLength, NULL, infoLog);
            cout << "\n\n\tShader Program Link Error\n\t" << infoLog 
            << "\n\tFor shader:  " << outputFile << "\n\n";
            exit(-1);
        }
        else
        {
            cout << "\n\n\tShader agregate program created "
            << "and the program has length " << progLength 
            << " bytes.\n\n";
        }
        // Delete the shaders as they're linked into our program now and no longer necessery
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if(createBinary())
        {
            cout << "\n\n\tShader program binary " << outputFile 
            << " compiled and saved.\n\n";
        }
        else
        {
            cout << "\n\n\tShader program binary " << outputFile 
            << " failed to compile and save.\n\n";
            if (debug1)
            {            
                exit(-1);
            }
        }
    }
}

unsigned int Shader::createShader(unsigned int type, string fpath)
{
    char c;
    string shaderCode;
    unsigned int shaderobj;
    FILE *shaderFile = fopen(fpath.c_str(), "r");
    if (!shaderFile)
    {
        cout << "\n\n\tError opening file " << fpath << ".\n\n";
        return 0;
    }
    // Read file's buffer contents into streams
    while ((c = std::fgetc(shaderFile)) != EOF) 
    { // standard C I/O file reading loop
        shaderCode += c;
    }
    fclose(shaderFile);
    const GLchar* glShaderCode = shaderCode.c_str();
    // Vertex Shader
    try
    {
        shaderobj = glCreateShader(type);
        glGetShaderiv(shaderobj, GL_INFO_LOG_LENGTH, &infoLength);
        if ((!shaderobj) && (infoLength == 0))
        {
            cout << "\n\n\tError creating shader object:  " << fpath << ".\n\n";
            if (debug1)
            {            
                exit(-1);
            }
        }
        else if(infoLength > 0)
        {
            char infoLog[infoLength];
            glGetShaderInfoLog(shaderobj, infoLength, NULL, infoLog);
            cout << "\n\nShader Program Creation Error\n" << infoLog << "\n\tFor shader:  " << fpath << ".\n\n";
            if (debug1)
            {            
                exit(-1);
            }
        }
        else
        {
            cout << "\n\n\tCreated the shader object:  " << fpath << ".\n\n";
        }
        glShaderSource(shaderobj, 1, &glShaderCode, nullptr);
        glCompileShader(shaderobj);
        // Print compile errors if any
        glGetShaderiv(shaderobj, GL_INFO_LOG_LENGTH, &infoLength);
        if ((!shaderobj) && (infoLength == 0))
        {
            cout << "\n\n\tError compiling shader object for shader:  " << fpath << ".\n\n";
            if (debug1)
            {            
                exit(-1);
            }
        }
        else if(infoLength > 0)
        {
            char infoLog[infoLength];
            glGetShaderInfoLog(shaderobj, infoLength, NULL, infoLog);
            cout << "\n\n\tShader compilation error: \n" << infoLog 
            << "\n\tFor shader " << fpath << "\n\n";
            glDeleteShader(shaderobj);
            return 0;
        }
        else
        {
             cout << "\n\n\tShader compiled.\n\n";
        }
        return shaderobj;
    }
    catch(exception exc)
    {
        cout << "\n\n\tError making shader:  " << exc.what() << "\n\n";
        return 0;
    }
}

void Shader::Use() 
{ 
    glUseProgram(Program); 
}   

bool Shader::createBinary()
{
    if (progLength <= 0)
    {
        cout << "\n\n\tShader program length less than one.\n\n";
        progLength = 1000000;
        if (debug1)
        {
            return false;
        }
    }
    binary = new unsigned char[progLength];
    glGetProgramBinary(Program, progLength, &progLenRet, &format, (GLvoid*) binary);
    if (progLength != progLenRet)
    {
        cout << "\n\n\tWarning program length of " << progLength 
        << " does not equal the size of the created binary "
        << progLenRet << " with format " << format
        << "\n\n";
        if (debug1)
        {
            return false;
        }
    }
    cout << "\n\n\tSaving shader binary at:  " << outputFile << ".\n\n";
    FILE *shaderFile = fopen(outputFile.c_str(), "wb");
    if (!shaderFile)
    {
        cout << "\n\n\tError opening file " << outputFile << ".\n\n";
        return false;
    }
    for (int x = 0; x < progLenRet; x++)
    { // Standard C I/O file writing loop.
       fputc(binary[x], shaderFile);
    }
    fclose(shaderFile);
    cout << "\n\n\tShader agregate binary program created "
    << "and saved.  The program has length " << progLenRet 
    << " bytes.\n\tAnd is saved at:  " << outputFile << ".\n\n";
    delete binary;
    return true;
}
    
void Shader::setBool(const std::string name, bool value) const
{         
    glUniform1i(glGetUniformLocation(Program, name.c_str()), (int)value); 
}
void Shader::setInt(const std::string name, int value) const
{ 
    glUniform1i(glGetUniformLocation(Program, name.c_str()), value); 
}
void Shader::setFloat(const std::string name, float value) const
{ 
    glUniform1f(glGetUniformLocation(Program, name.c_str()), value); 
} 
void Shader::setVec2(const std::string name, vec2 value) const
{ 
    glUniform2fv(glGetUniformLocation(Program, name.c_str()), 1, value_ptr(value)); 
} 
void Shader::setVec3(const std::string name, vec3 value) const
{ 
    glUniform3fv(glGetUniformLocation(Program, name.c_str()), 1, value_ptr(value)); 
} 
void Shader::setVec4(const std::string name, vec4 value) const
{ 
    glUniform4fv(glGetUniformLocation(Program, name.c_str()), 1, value_ptr(value)); 
} 
void Shader::setMat4(const std::string name, mat4 value) const
{ 
    glUniformMatrix4fv(glGetUniformLocation(Program, name.c_str()), 1, GL_FALSE, &value[0][0]); 
} 
