/*******************************************************************
 * Shader:  A class to encapsulate the creation and use of a set of
 * shaders.  
 * Edward C. Eberle <eberdeed@eberdeed.net>
 * March 2020 San Diego, California USA
 * ****************************************************************/

#ifndef SHADER_H
#define SHADER_H

#include "commonheader.h"

using namespace std;
using namespace glm;
/** \class Shader A class to encapsulate the uploading, compiling, 
 * linking and use of a shader.  This class will create a shader 
 * binary and reload it.  The binary will be recreated if it ceases 
 * to validate as a shader program.
 */

class Shader
{
public:
    /** \brief The constructor signals the creation of the class.
     */
    Shader();
    /** \brief The destructor signals the destruction of the class,
     *  and deletes the shader program.
     */  
    ~Shader();
    /** \brief Read and build the shader program from two files,
     *  and provide the file name for the created binary.
     *  Delete the two shader objects afterwards.
     *  The variables are as follows:
     *  vertexPath : The vertex shader's location in the file structure.
     *  fragmentPath : The fragment shader's location in the file structure.
     *  outputFile : The name given to the output binary.
     *  The program will load and rely on the created binary
     *  after it is made.
     */
    void initShader(string vertexPath, string fragmentPath, 
    string outputFile);
    /** \brief Create either the vertex or fragment shader from a file.
     */
    unsigned int createShader(unsigned int type, string fpath);
    /** \brief Use the program object for display.
     */
    void Use();
    /** \brief Create the shader program binary save it to a file,
     * and delete the binary pointer afterward.
     */
    bool createBinary();
    /** \brief Utility uniform functions that set values in the shader program.
     */
    void setBool(const string name, bool value) const;  
    void setInt(const string name, int value) const;   
    void setFloat(const string name, float value) const;
    void setVec2(const std::string name, vec2 value) const;
    void setVec3(const std::string name, vec3 value) const;
    void setVec4(const string name, vec4 value) const; 
    void setMat4(const string name, mat4 value) const;    
    
    /** Variables **/
    //! The shader program object.
    GLuint Program;
    //! Class global variables.
    //! Debugging information.
    bool debug1 = false;
    //! Indicates success of OpenGL function calls.
    int success = 0;
    //! Length of an OpenGL error information message.
    int infoLength = 0;
    //! Handles for vertex and fragment shaders respectively.
    GLuint vertex, fragment;
    //! The length of the program in bytes.
    int progLength = 0;
    //! The length of the program binary in bytes.
    int progLenRet = 0;
    //! Formats for the stored binary program.
    GLenum *valFormats;
    GLenum format = 0;
    //! A variable indicating the successful loading of a stored program binary.
    int response = 0;
    //! The binary program pointer.
    unsigned char *binary;
    /** The output file name.  The final stored binary is stored
     * int the .config directory of the user's home directory (~/.config).
     */
    string outputFile;

};
  
#endif //SHADER_H
