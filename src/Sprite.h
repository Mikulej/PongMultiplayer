#ifndef SPRITE_H
#define SPRITE_H
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "shader.h"
#include "glm-master/glm/glm.hpp"
#include "glm-master/glm/gtc/matrix_transform.hpp"
#include "glm-master/glm/gtc/type_ptr.hpp"
#include <stb_image.h>

using namespace std;
enum class VaoType { CENTER, BOTTOM_LEFT };
class Sprite final {
	static std::unordered_map<std::string,unsigned int> textures;
	static std::unordered_map<VaoType, std::tuple<unsigned, unsigned, unsigned>> vaos;
	
	Sprite(unsigned int _texture, float _x = 0, float _y = 0, unsigned int _layer = 0, VaoType _VAO = VaoType::CENTER);
	static unsigned int generateTexture(std::string path);
	static std::tuple<unsigned, unsigned, unsigned> generateVao(const VaoType& v);
	glm::vec4 Pos;
	glm::vec4 Scale;
	glm::vec4 Color;
	glm::vec2 Offset;
	glm::vec2 Zoom;
	float angle;
	int layer;
	unsigned int texture;
	//int height;
	//int width;
	VaoType vaoType;
	//unsigned int vaoType;
	
	bool isRendered;
public:
	static std::vector<Sprite> renderList; // is public solely for tests
	static void Initialize(void);
	static void DeleteTextures(void);
	~Sprite() = default;
	static void RenderAll(Shader& ourShader);
	static int AddSprite(std::string _texture, float _x = 0, float _y = 0, unsigned int _layer = 0, VaoType _VAO = VaoType::CENTER);
	static void DeleteSprite(unsigned int _ID);
	void DeleteSprite();
	//MATRIX MAINPULATION
	void setColor(int _c = -1, bool _marked = false);
	void setScale(float x, float y);
	void setPos(float x, float y);
};
#endif