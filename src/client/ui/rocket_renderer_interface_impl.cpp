/*
 * client/ui/rocket_renderer_interface_impl.cpp
 *
 * Copyright (c) 2012
 * Marcin Koziuk <marcin.koziuk@gmail.com>
 */

/*
 * This source file is part of libRocket, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://www.librocket.com
 *
 * Copyright (c) 2008-2010 Nuno Silva
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <iostream>
#include <string>
#include <Rocket/Core/Core.h>

#include <gravity/client/ui/rocket_renderer_interface_impl.hpp>
#include <gravity/game/logging.hpp>



#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/gl.h>

using namespace std;


RocketRendererInterfaceImpl::RocketRendererInterfaceImpl()
{}

RocketRendererInterfaceImpl::~RocketRendererInterfaceImpl()
{}

// Called by Rocket when it wants to render geometry that it does not wish to optimise.
void RocketRendererInterfaceImpl::RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, const Rocket::Core::TextureHandle Image, const Rocket::Core::Vector2f& translation)
{
	if(!target)
		return;

    target->resetGLStates();
	target->pushGLStates();
	//glPushMatrix();

    sf::View view = target->getDefaultView();
	sf::VertexArray v(sf::Triangles, num_indices);
	for(int j = 0; j < num_indices; j++){ //iterate indices
		int i = indices[j]; //i is the vertex position.
		v[j].position = sf::Vector2f(vertices[i].position.x, vertices[i].position.y);
		v[j].color = sf::Color(vertices[i].colour.red,vertices[i].colour.green,vertices[i].colour.blue, vertices[i].colour.alpha);
		if(Image){
			v[j].texCoords = sf::Vector2f(vertices[i].tex_coord.x*((sf::Texture*)Image)->getSize().x, vertices[i].tex_coord.y*((sf::Texture*)Image)->getSize().y);
		}
	}

	states->blendMode = sf::BlendAlpha;
	states->texture = (sf::Texture*)Image;

    view.move(sf::Vector2f(-translation.x, -translation.y));
    target->setView(view);
	target->draw(v, *states);

	target->popGLStates();
    //target->resetGLStates();
}
 
// Called by Rocket when it wants to compile geometry it believes will be static for the forseeable future.		
Rocket::Core::CompiledGeometryHandle RocketRendererInterfaceImpl::CompileGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, const Rocket::Core::TextureHandle Image)
{
	return (Rocket::Core::CompiledGeometryHandle)NULL;
}

// Called by Rocket when it wants to render application-compiled geometry.		
void RocketRendererInterfaceImpl::RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation)
{
}

// Called by Rocket when it wants to release application-compiled geometry.		
void RocketRendererInterfaceImpl::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry)
{
}

// Called by Rocket when it wants to enable or disable scissoring to clip content.		
void RocketRendererInterfaceImpl::EnableScissorRegion(bool enable)
{
	if (enable)
		glEnable(GL_SCISSOR_TEST);
	else
		glDisable(GL_SCISSOR_TEST);
}

// Called by Rocket when it wants to change the scissor region.
void RocketRendererInterfaceImpl::SetScissorRegion(int x, int y, int width, int height)
{
	glScissor(x, target->getSize().y - (y + height), width, height);
}

// Called by Rocket when a Image is required by the library.		
bool RocketRendererInterfaceImpl::LoadTexture(Rocket::Core::TextureHandle& Image_handle, Rocket::Core::Vector2i& Image_dimensions, const Rocket::Core::String& source)
{
	sf::Texture *texture = new sf::Texture();

	if(!texture->loadFromFile(std::string("../data/gui/") + source.CString()))
	{
		delete texture;

		return false;
	};

	Image_handle = (Rocket::Core::TextureHandle) texture;
	Image_dimensions = Rocket::Core::Vector2i(texture->getSize().x, texture->getSize().y);

	return true;
}

// Called by Rocket when a Image is required to be built from an internally-generated sequence of pixels.
bool RocketRendererInterfaceImpl::GenerateTexture(Rocket::Core::TextureHandle& Image_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions)
{
	sf::Image *image = new sf::Image();
	sf::Texture *texture = new sf::Texture();

	image->create(source_dimensions.x, source_dimensions.y, source);

	texture->loadFromImage(*image);
	Image_handle = (Rocket::Core::TextureHandle)texture;

	return true;
}

// Called by Rocket when a loaded Image is no longer required.		
void RocketRendererInterfaceImpl::ReleaseTexture(Rocket::Core::TextureHandle Image_handle)
{
	delete (sf::Texture*)Image_handle;
}












#if 0
#ifdef ENABLE_GLEW
#include <gl/glew.h>
#endif

#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif
// If built with the GL Easy Extension library we can compile geometry to VBO's
// http://www.opengl.org/sdk/libs/GLee/
#ifdef ENABLE_GLEW

class RocketRendererInterfaceImplGeometryHandler
{
public:
	GLuint VertexID, IndexID;
	int NumVertices;
	Rocket::Core::TextureHandle Texture;

	RocketRendererInterfaceImplGeometryHandler() : VertexID(0), IndexID(0), Texture(0), NumVertices(0)
	{
	};

	~RocketRendererInterfaceImplGeometryHandler()
	{
		if(VertexID)
			glDeleteBuffers(1, &VertexID);

		if(IndexID)
			glDeleteBuffers(1, &IndexID);

		VertexID = IndexID = 0;
	};
};

#endif

struct RocketRendererInterfaceImplVertex
{
	sf::Vector2f Position, TexCoord;
	sf::Color Color;
};

RocketRendererInterfaceImpl::RocketRendererInterfaceImpl()
{
}

void RocketRendererInterfaceImpl::SetWindow(sf::RenderWindow *Window)
{
	MyWindow = Window;

	Resize();
};

sf::RenderWindow *RocketRendererInterfaceImpl::GetWindow()
{
	return MyWindow;
};

void RocketRendererInterfaceImpl::Resize()
{
	//MyWindow->SetActive(true);
	//MyWindow->SaveGLStates();

	static sf::View View;
	//View.SetFromRect(sf::FloatRect(0, (float)MyWindow->GetWidth(), (float)MyWindow->GetHeight(), 0));
	//View.SetViewport(sf::FloatRect(0, (float)MyWindow->GetWidth(), (float)MyWindow->GetHeight(), 0));
	//MyWindow->SetView(View);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, MyWindow->GetWidth(), MyWindow->GetHeight(), 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);

	glViewport(0, 0, MyWindow->GetWidth(), MyWindow->GetHeight());

	//MyWindow->RestoreGLStates();
};

// Called by Rocket when it wants to render geometry that it does not wish to optimise.
void RocketRendererInterfaceImpl::RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, const Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation)
{
	//MyWindow->SetActive();
	glPushMatrix();
	glTranslatef(translation.x, translation.y, 0);

	std::vector<Rocket::Core::Vector2f> Positions(num_vertices);
	std::vector<Rocket::Core::Colourb> Colors(num_vertices);
	std::vector<Rocket::Core::Vector2f> TexCoords(num_vertices);

	for(int  i = 0; i < num_vertices; i++)
	{
		Positions[i] = vertices[i].position;
		Colors[i] = vertices[i].colour;
		TexCoords[i] = vertices[i].tex_coord;
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(2, GL_FLOAT, 0, &Positions[0]);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, &Colors[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &TexCoords[0]);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	sf::Texture *image = (sf::Texture *)texture;

	if(image)
	{
		image->Bind();
		//image->Bind();
	}
	else
	{
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindTexture(GL_TEXTURE_2D, 0);
	};

	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, indices);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glColor4f(1, 1, 1, 1);

	glPopMatrix();
}

// Called by Rocket when it wants to compile geometry it believes will be static for the forseeable future.		
Rocket::Core::CompiledGeometryHandle RocketRendererInterfaceImpl::CompileGeometry(Rocket::Core::Vertex* vertices,
																		   int num_vertices, int* indices,
																		   int num_indices,
																		   const Rocket::Core::TextureHandle texture)
{
#ifdef ENABLE_GLEW
	//MyWindow->SetActive();

	//if(!GLEE_VERSION_2_0)
		//return (Rocket::Core::CompiledGeometryHandle) NULL;

	std::vector<RocketRendererInterfaceImplVertex> Data(num_vertices);

	for(unsigned long i = 0; i < Data.size(); i++)
	{
		Data[i].Position = *(sf::Vector2f*)&vertices[i].position;
		Data[i].TexCoord = *(sf::Vector2f*)&vertices[i].tex_coord;
		Data[i].Color = sf::Color(vertices[i].colour.red, vertices[i].colour.green,
			vertices[i].colour.blue, vertices[i].colour.alpha);
	};

	RocketRendererInterfaceImplGeometryHandler *Geometry = new RocketRendererInterfaceImplGeometryHandler();
	Geometry->NumVertices = num_indices;

	glGenBuffers(1, &Geometry->VertexID);
	glBindBuffer(GL_ARRAY_BUFFER, Geometry->VertexID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(RocketRendererInterfaceImplVertex) * num_vertices, &Data[0],
		GL_STATIC_DRAW);

	glGenBuffers(1, &Geometry->IndexID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Geometry->IndexID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * num_indices, indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	Geometry->Texture = texture;

	return (Rocket::Core::CompiledGeometryHandle)Geometry;
#else
	return NULL;
#endif
}

// Called by Rocket when it wants to render application-compiled geometry.		
void RocketRendererInterfaceImpl::RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry, const Rocket::Core::Vector2f& translation)
{
#ifdef ENABLE_GLEW
	//MyWindow->SetActive();
	RocketRendererInterfaceImplGeometryHandler *RealGeometry = (RocketRendererInterfaceImplGeometryHandler *)geometry;

	//glPushMatrix();
	//glTranslatef(translation.x, translation.y, 0);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	sf::Texture *image = (sf::Texture *)RealGeometry->Texture;

	if(image)
	{
		image->Bind();
	}
	else
	{
	//	glBindTexture(GL_TEXTURE_2D, 0);
	};

	//glEnable(GL_VERTEX_ARRAY);
	//glEnable(GL_TEXTURE_COORD_ARRAY);
	//glEnable(GL_COLOR_ARRAY);

	#define BUFFER_OFFSET(x) ((char*)0 + x)

	glBindBuffer(GL_ARRAY_BUFFER, RealGeometry->VertexID);
	glVertexPointer(2, GL_FLOAT, sizeof(RocketRendererInterfaceImplVertex), BUFFER_OFFSET(0));
	glTexCoordPointer(2, GL_FLOAT, sizeof(RocketRendererInterfaceImplVertex), BUFFER_OFFSET(sizeof(sf::Vector2f)));
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(RocketRendererInterfaceImplVertex), BUFFER_OFFSET(sizeof(sf::Vector2f[2])));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, RealGeometry->IndexID);
	glDrawElements(GL_TRIANGLES, RealGeometry->NumVertices, GL_UNSIGNED_INT, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//glDisable(GL_COLOR_ARRAY);
	//glDisable(GL_TEXTURE_COORD_ARRAY);
	//glDisable(GL_VERTEX_ARRAY);

	glColor4f(1, 1, 1, 1);

	//glPopMatrix();
#else
	ROCKET_ASSERT(false /*& "Not Implemented"*/);
#endif
}

// Called by Rocket when it wants to release application-compiled geometry.		
void RocketRendererInterfaceImpl::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle geometry)
{
#ifdef ENABLE_GLEW
	//MyWindow->SetActive();

	delete (RocketRendererInterfaceImplGeometryHandler *)geometry;
#else
	ROCKET_ASSERT(false /*& "Not Implemented"*/);
#endif
}

// Called by Rocket when it wants to enable or disable scissoring to clip content.		
void RocketRendererInterfaceImpl::EnableScissorRegion(bool enable)
{
	//MyWindow->SetActive();

	if (enable)
		glEnable(GL_SCISSOR_TEST);
	else
		glDisable(GL_SCISSOR_TEST);
}

// Called by Rocket when it wants to change the scissor region.		
void RocketRendererInterfaceImpl::SetScissorRegion(int x, int y, int width, int height)
{
	//MyWindow->SetActive();

	glScissor(x, MyWindow->GetHeight() - (y + height), width, height);
}

// Called by Rocket when a texture is required by the library.		
bool RocketRendererInterfaceImpl::LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source)
{
	//MyWindow->SetActive();

	Rocket::Core::FileInterface* file_interface = Rocket::Core::GetFileInterface();
	Rocket::Core::FileHandle file_handle = file_interface->Open(source);
	if (file_handle == NULL)
		return false;

	file_interface->Seek(file_handle, 0, SEEK_END);
	size_t buffer_size = file_interface->Tell(file_handle);
	file_interface->Seek(file_handle, 0, SEEK_SET);

	char* buffer = new char[buffer_size];
	file_interface->Read(buffer, buffer_size, file_handle);
	file_interface->Close(file_handle);

	sf::Texture *image = new sf::Texture();

	if(!image->LoadFromMemory(buffer, buffer_size))
	{
		delete buffer;
		delete image;

		return false;
	};
	delete buffer;

	texture_handle = (Rocket::Core::TextureHandle) image;
	texture_dimensions = Rocket::Core::Vector2i(image->GetWidth(), image->GetHeight());

	return true;
}

// Called by Rocket when a texture is required to be built from an internally-generated sequence of pixels.
bool RocketRendererInterfaceImpl::GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions)
{
	//MyWindow->SetActive();
	//sf::Image *image = new sf::Image();

	sf::Texture *image = new sf::Texture();
	image->Create(source_dimensions.x, source_dimensions.y);
	image->Update(source, source_dimensions.x, source_dimensions.y, 0, 0);

	/*if(!image->Create(source_dimensions.x, source_dimensions.y, source))
	{
		delete image;

		return false;
	};*/

	texture_handle = (Rocket::Core::TextureHandle)image;

	return true;
}

// Called by Rocket when a loaded texture is no longer required.		
void RocketRendererInterfaceImpl::ReleaseTexture(Rocket::Core::TextureHandle texture_handle)
{
	//MyWindow->SetActive();

	delete (sf::Texture *)texture_handle;
}

#endif