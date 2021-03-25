/**********************************************************
 *   Mesh:  A class to be a base class for MeshTex 
 *   (textured meshes) and MeshVert (untextured meshes).  
 *   This class isolates that acquisition of data from a 
 *   3d asset file using assimp.
 *   This is an abstract class that is not to be instantiated,
 *   but only used as a pointer for the derived classes.
 *   Adapted by: Edward Charles Eberle <eberdeed@eberdeed.net>
 *   and originally found on www.learnopengl.com
 *   April 2020 San Diego, California USA
 * ********************************************************/

#ifndef MESH_H
#define MESH_H


#include "commonheader.h"
#include "shader.h"
#include <vector>

//! Forward declarations so it can be used as a library.
struct Vertex;
struct Vertex1;
struct PointLight;
struct SpotLight;
struct Texture;
class Shader;
/** \class Mesh A class that is a base class for the two classes
 * MeshTex (textured meshes) and MeshVert (untextured meshes).
 * Used as a generic pointer for both.
 */
class Mesh {
public:
    //! \brief Constructor echoing its creation (should not occur).
    Mesh();
    //! \brief Destructor echoing its destruction (should not occur).
    ~Mesh();
    /*  Functions  */
    /** \brief Set data for MeshTex.
     * vertices : The vertex array.
     * indices : The index array.
     * textures : The texture vector.
     * vertSize : The number of vertices.
     * indexSize : The number of indices.
     * instanced : The instancing flag.
     * quantity : The number of instances.
     * shader : The shader.
     * explodeShader the shader for the explosion.
     * cloudShader the shader for the gaseous cloud during
     * the explosion.
     * startIndex : The starting index for the texture buffers.
     */
    int setData(Vertex *vertices, GLuint *indices, vector<Texture>textures, 
    int vertSize, int indexSize, bool instanced, int quantity, 
    Shader *shader, Shader *explodeShader, Shader *cloudShader, int startIndex);
    /** \brief Set data for MeshVert.
     * vertices : The vertex array.
     * indices : The index array.
     * vertSize : The number of vertices.
     * indexSize : The number of indices.
     * instanced : The instancing flag.
     * quantity : The number of instances.
     * shader : The shader.
     */
    void setData(Vertex1 *vertices, GLuint *indices, int vertSize, int indexSize, bool instanced, int quanity, Shader *shader );
    /** \brief A virtual function implemented and used by both classes.
     * view is the position and orientation of the camera.  
     * projection is the perspective for which I use the perspective funcition
     * of GLM in the camera class. 
     * model is the position and orientation of the mesh being drawn.
     * lights are point lights defined by the PointLight structure.
     * spotLights are spotlights defined by the SpotLight structure.
     * viewPos is the camera position.
     * startIndex is the current index of the textures being used.
     * diffOnly when set to true will provide an image without specular highlights.
     * gamma controls brightness of the textured mesh.
     */
    virtual void Draw(mat4 view, mat4 projection, mat4 model, 
    vector<PointLight> lights, vector<SpotLight>spotLights, 
    vec3 viewPos, bool diffOnly = true, float gamma = 1.0f);
    /** \brief A virtual function implemented and used by both classes to draw 
     * instanced data. The only difference from the above is that the model 
     * variable is a vector.  
     * view is the position and orientation of the camera.  
     * projection is the perspective for which I use the 
     * perspective funcition
     * of GLM in the camera class. 
     * model is a vector of the various positions and orientations 
     * of the instances of the mesh being drawn.
     * lights are point lights defined by the PointLight structure.
     * spotLights are spotlights defined by the SpotLight structure.
     * viewPos is the camera position.
     * startIndex is the current index of the textures being used.
     * diffOnly when set to true will provide an image without specular highlights.
     * gamma controls brightness of the textured mesh.
     */
    virtual void DrawInstanced(mat4 view, mat4 projection, vector<mat4>model, 
    vector<PointLight> lights, vector<SpotLight>spotLights, vec3 viewPos, 
    bool diffOnly = true, float gamma = 1.0f);
    //! \brief Blow up the object.
    virtual void explosion(mat4 model, mat4 view, mat4 projection, float timeVal);
    //! \brief A convenience function to pass messages.
    string getType();
    //! \brief A convenience function to post messages.
    void setType(string val);
    //! \brief Data checking. Provides vertex, normal, index and perhaps texture coordinate output.
    void dumpData();
    //! \brief Set the vertex array and index buffer.
    virtual void setupMesh();
    /* Variables */
    //! Message data.
    string type;
    //! The object's opaqueness.
    float opacity;
    //! The instancing locations.
    vector<mat4>instanceMatrices;
    //! The pointer to the instance array.
    mat4 *instanceArray;
    //! The instancing flag.
    bool instanced = false;
    //! The instancing quantity and the uniform index.
    int quantity = 1, dataIndex = 0;
    //! The instancing shader.
    Shader *shader = nullptr;
public:
    //! The Vertex array.
    Vertex *vertices;
    //! The indexed Vertex array.
    Vertex *verticesIndexed;
    //! Sampler values.
    unsigned intdummyTex = 500;
    //! These booleans indicate no diffuse, specular or binormal textures
    //! have been assigned.  When the program assigns a valid buffer 
    //! value for that texture they are triggered to false.  Later they
    //! are used to assign dummy values to buffers with no texture.
    bool difftrigger = true;
    bool spectrigger = true;
    bool heighttrigger = true;
    //! These booleans are switched to true if there is a diffuse, specular
    //! or binormal texture found.
    bool isDiff, isDiffTwo, isSpec, isBinorm;
    //! These integers contain the buffer values for the diffuse, specular
    //! and binormal textures.  If no texture is assigned a dummy value is given.
    int diffOne, diffTwo, specOne, binormOne, dummyTex = 500;
    //! These integers tell what the index of the texture is for each type of texture.
    //! numDiff is the number of diffuse textures.
    int diffOneX, diffTwoX, specOneX, binormOneX, numDiff;  
    
};


#endif // MESH_H
