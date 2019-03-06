#include "pch.h"

#include <Kore/IO/FileReader.h>
#include <Kore/Graphics4/Graphics.h>
#include <Kore/Graphics4/PipelineState.h>
#include <Kore/Graphics4/Shader.h>
#include <Kore/System.h>
#include <stdlib.h>

using namespace Kore;

namespace {
	Graphics4::Shader* vertexShader;
	Graphics4::Shader* fragmentShader;
	Graphics4::PipelineState* pipeline;
	Graphics4::VertexBuffer* vertices;
	Graphics4::IndexBuffer* indices;
	Graphics4::ConstantLocation projectionLocation;

	Window* window;

	int width;
	int height;

	float random( float a, float b ) {
		return ( ( b - a ) * ( ( float ) rand() / RAND_MAX ) ) + a;
	}

	void update() {

		float halfWidth = width / 2;
		float halfHeight = height / 2;

		Graphics4::begin();
		Graphics4::clear(Graphics4::ClearColorFlag);

		// lock vertex buffer
		float* v = vertices->lock();
		// update position of triangle
		v[0] = halfWidth + random( -100.0, 100.0 ); // x1
		v[1] = halfHeight + random( -100.0, 100.0 ); // y1
		v[7] = halfWidth + random( -100.0, 100.0 ); // x1
		v[8] = halfHeight + random( -100.0, 100.0 ); // y1
		v[14] = halfWidth + random( -100.0, 100.0 ); // x1
		v[15] = halfHeight + random( -100.0, 100.0 ); // y1
		// unlock vertex buffer
		vertices->unlock();
		
		// 
		Graphics4::setPipeline(pipeline);
		Graphics4::setVertexBuffer(*vertices);
		Graphics4::setIndexBuffer(*indices);

		// set camera projection
		Graphics4::setMatrix( projectionLocation, mat4::orthogonalProjection(0.f, static_cast<float>(width), static_cast<float>(height), 0.f, 0.f, 1000.f));

		// draw vertices
		Graphics4::drawIndexedVertices();

		Graphics4::end();
		Graphics4::swapBuffers();
	}
}

int kore(int argc, char** argv) {

	width = 1440;
	height = 900;

	Kore::WindowOptions windowOptions;
	windowOptions.width = width;
	windowOptions.height = height;
	//windowOptions.windowFeatures = WindowFeatureBorderless;
	windowOptions.mode = Kore::WindowMode::WindowModeExclusiveFullscreen;

	Kore::System::init("Vie", width, height, &windowOptions);
	Kore::System::setCallback(update);

	FileReader vs("shader.vert");
	FileReader fs("shader.frag");
	vertexShader = new Graphics4::Shader(vs.readAll(), vs.size(), Graphics4::VertexShader);
	fragmentShader = new Graphics4::Shader(fs.readAll(), fs.size(), Graphics4::FragmentShader);

	//
	Graphics4::VertexStructure structure;
	structure.add("pos", Graphics4::Float3VertexData);
	structure.add("col", Graphics4::Float4VertexData);

	// create pipeline state
	pipeline = new Graphics4::PipelineState();
	pipeline->vertexShader = vertexShader;
	pipeline->fragmentShader = fragmentShader;
	pipeline->inputLayout[0] = &structure;
	pipeline->inputLayout[1] = nullptr;
	pipeline->compile();

	// store projection location
	projectionLocation = pipeline->getConstantLocation("projectionMatrix");

	// create vertex buffer
	vertices = new Graphics4::VertexBuffer(3, structure, Graphics4::Usage::DynamicUsage);
	// lock vertex buffer
	float* v = vertices->lock();
	// populate vertex buffer
	v[0] = -1.0; // x1
	v[1] = -1.0; // y1
	v[2] = 0.0; // z1
	v[3] = 1.0; // r1
	v[4] = 0.0; // g1
	v[5] = 0.0; // b1
	v[6] = 1.0; // a1
	v[7] = 1.0; // x1
	v[8] = -1.0; // y1
	v[9] = 0.0; // z1
	v[10] = 0.0; // r2
	v[11] = 1.0; // g2
	v[12] = 0.0; // b2
	v[13] = 1.0; // a2
	v[14] = -1.0; // x3
	v[15] = 1.0; // y3
	v[16] = 0.0; // z3
	v[17] = 0.0; // r3
	v[18] = 0.0; // g3
	v[19] = 1.0; // b3
	v[20] = 1.0; // a3
	// unlock vertex buffer
	vertices->unlock();

	// create index buffer
	indices = new Graphics4::IndexBuffer(3);
	// lock index buffer
	int* i = indices->lock();
	// populate index buffer
	i[0] = 0; i[1] = 1; i[2] = 2;
	// unlock index buffer
	indices->unlock();

	Kore::System::start();

	return 0;
}