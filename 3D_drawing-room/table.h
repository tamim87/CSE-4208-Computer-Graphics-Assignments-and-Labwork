#ifndef table_h
#define table_h

#include "shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include<vector>


class Table {

public:
	std::vector<glm::mat4> modelMatrices;
	float tox, toy, toz;
	Table(float x = 0, float y = 0, float z = 0) {
		tox = x;
		toy = y;
		toz = z;
	}
	glm::mat4 transforamtion(float tx, float ty, float tz, float rx, float ry, float rz, float sx, float sy, float sz) {
		tx += tox;
		ty += toy;
		tz += toz;
		glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
		translateMatrix = glm::translate(identityMatrix, glm::vec3(tx, ty, tz));
		rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rx), glm::vec3(1.0f, 0.0f, 0.0f));
		rotateYMatrix = glm::rotate(identityMatrix, glm::radians(ry), glm::vec3(0.0f, 1.0f, 0.0f));
		rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rz), glm::vec3(0.0f, 0.0f, 1.0f));
		scaleMatrix = glm::scale(identityMatrix, glm::vec3(sx, sy, sz));
		model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
		return model;
	}

	Shader local_rotation(Shader ourShader, unsigned int  VAO, unsigned int VAOF3, unsigned int VAO3, unsigned int VAO2, unsigned int VAOW2, float angle = 0) {
		glm::mat4 model;
		float rotateAngle_X = 0;
		float rotateAngle_Y = 0;
		float rotateAngle_Z = 0;

		model = transforamtion(-.20, 0, 0.00, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 3.6, 0.2, 2.6);
		modelMatrices.push_back(model);

		model = transforamtion(0, 0, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.2, -1.5, 0.2);
		modelMatrices.push_back(model);

		model = transforamtion(1.35, 0, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.2, -1.5, 0.2);
		modelMatrices.push_back(model);

		model = transforamtion(1.35, 0, 1.2, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.2, -1.5, 0.2);
		modelMatrices.push_back(model);

		model = transforamtion(0, 0, 1.2, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.2, -1.5, 0.2);
		modelMatrices.push_back(model);

		//model = transforamtion(0.4, 0, 1.8, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 3.6, 0.2, 2.5);

		model = transforamtion(0.0, -.75, 2.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 3.6, 1.1, -1.538);
		modelMatrices.push_back(model);

		model = transforamtion(0.0, -.75, -0.4, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 3.6, 1.1, -1.538);
		modelMatrices.push_back(model);

		model = transforamtion(0.0, -.85, 2.56, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 3.6, 3.0, -.13);
		modelMatrices.push_back(model);

		model = transforamtion(0.0, -.85, -1.17, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 3.6, 3.0, -.13);
		modelMatrices.push_back(model);


		unsigned int vertex_array[] = { VAO, VAOF3, VAO3, VAO2, VAOW2 };
		glm::vec3 averagePosition(0.0f);
		for (const glm::mat4& model : modelMatrices) {
			averagePosition += glm::vec3(model[3]);
		}
		averagePosition /= modelMatrices.size();

		glm::mat4 moveToOrigin = glm::translate(glm::mat4(1.0f), -averagePosition);

		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));

		glm::mat4 moveToOriginalPosition = glm::translate(glm::mat4(1.0f), averagePosition);

		glm::mat4 groupTransform = moveToOriginalPosition * rotation * moveToOrigin;

		int i = 0;
		for (glm::mat4& model : modelMatrices) {

			model = groupTransform * model;
			ourShader.setMat4("model", model);
			glBindVertexArray(vertex_array[i]);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
			i++;
		}
		return ourShader;
	}

	Shader ret_shader(Shader ourShader, unsigned int VAO, unsigned int VAOB, unsigned int VAO3, unsigned int VAO2, unsigned int VAOW2) {
		glm::mat4 model;
		float rotateAngle_X = 0;
		float rotateAngle_Y = 0;
		float rotateAngle_Z = 0;

		model = transforamtion(-.20, 0, 0.0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 3.6, 0.2, 2.6+4);
		ourShader.setMat4("model", model);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		//Leg
		model = transforamtion(0, 0, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.2, -1.5, 0.2);
		modelMatrices.push_back(model);
		ourShader.setMat4("model", model);
		glBindVertexArray(VAOB);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		//Leg
		model = transforamtion(1.35, 0, 0, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.2, -1.5, 0.2);
		modelMatrices.push_back(model);
		ourShader.setMat4("model", model);
		glBindVertexArray(VAOB);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		//Leg
		model = transforamtion(1.35, 0, 1.2+2, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.2, -1.5, 0.2);
		modelMatrices.push_back(model);
		ourShader.setMat4("model", model);
		glBindVertexArray(VAOB);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		//Leg
		model = transforamtion(0, 0, 1.2+2, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 0.2, -1.5, 0.2);
		modelMatrices.push_back(model);
		ourShader.setMat4("model", model);
		glBindVertexArray(VAOB);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		////chair_Top
		//model = transforamtion(0.4, 0, 1.8, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 3.6, 0.2, 2.5);
		//modelMatrices.push_back(model);
		//ourShader.setMat4("model", model);
		//glBindVertexArray(VAO3);
		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		////c_bottom
		//model = transforamtion(0.0, -.75, 2.5, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 3.6, 1.1, -1.538);
		//modelMatrices.push_back(model);
		//ourShader.setMat4("model", model);
		//glBindVertexArray(VAO3);
		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		////c_bottom2
		//model = transforamtion(0.0, -.75, -0.4, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 3.6, 1.1, -1.538);
		//modelMatrices.push_back(model);
		//ourShader.setMat4("model", model);
		//glBindVertexArray(VAO3);
		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		////back
		//model = transforamtion(0.0, -.85, 2.56, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 3.6, 3.0, -.13);
		//modelMatrices.push_back(model);
		//ourShader.setMat4("model", model);
		//glBindVertexArray(VAO2);
		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		////back2
		//model = transforamtion(0.0, -.85, -1.17, rotateAngle_X, rotateAngle_Y, rotateAngle_Z, 3.6, 3.0, -.13);
		//modelMatrices.push_back(model);
		//ourShader.setMat4("model", model);
		//glBindVertexArray(VAO4);
		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

		//glBindVertexArray(VAO5);
		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


		return ourShader;
	}
};


#endif