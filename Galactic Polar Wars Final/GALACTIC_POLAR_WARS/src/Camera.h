//#pragma once
//#include <vector>
//#include <GLM\glm\detail\type_vec.hpp>
//
//using namespace std;
//
//class Camera
//{
//public: 
//	static Camera* Instance()
//	{
//		if (s_pCamera == 0)
//		{
//			s_pCamera = new Camera();
//		}
//		return s_pCamera;
//	}
//
//	void update(glm::vec2 velocity);
//
//	void setTarget(glm::vec2* target)
//	{
//		m_pTarget = target;
//	}
//
//	void setPosition(const glm::vec2& position)
//	{
//		m_position = position;
//	}
//
//	const glm::vec2 getPosition() const;
//
//private: 
//	Camera();
//	~Camera();
//
//	//The camera's target
//	glm::vec2* m_pTarget;
//
//	//The camera's position
//	glm::vec2 m_position;
//
//	static Camera* s_pCamera;
//};
//
//typedef Camera TheCamera;