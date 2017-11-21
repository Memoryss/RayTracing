#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <memory>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/detail/func_geometric.hpp>
#include <glm/detail/func_common.hpp>
#include "Ray.h"
#include "Light.h"
#include <iostream>

namespace RayTracing
{
    class Material
    {
    public:
        Material(float reflectiveness) : m_reflectiveness(reflectiveness) {}

        //����
        virtual glm::vec4 ray(std::shared_ptr<Ray> ray, std::shared_ptr<Light> light, glm::vec3 position, glm::vec3 normal) = 0;

        float GetReflectiveness() { return m_reflectiveness; }

    private:
        float m_reflectiveness{};       //���������  0��ʾ������ ����ȫ������

    };

    /**
    blinn-phongģ�Ͳ���
    */
    class PhongMaterial : public Material
    {
    public:
		PhongMaterial(const glm::vec3 &kd, const glm::vec3 &ks, float shininess, float reflectiveness = 0)
			: m_kd(kd), m_ks(ks), m_shininess(shininess), Material(reflectiveness)
		{

		}

        virtual glm::vec4 ray(std::shared_ptr<Ray> ray, std::shared_ptr<Light> light, glm::vec3 position, glm::vec3 normal) override
        {
            normal = glm::normalize(normal);
            auto direction = glm::normalize(light->GetDirection(position));

            float diffuseFactor = glm::max(0.f, dot(normal, -direction));
            glm::vec3 diffuseColor = m_kd * diffuseFactor * light->m_color;

            float specularFactor = 0.f;
            //phong
            {
                //���㷴�����
                glm::vec3 R = glm::normalize(direction - normal *(glm::dot(normal, direction) * 2));
                specularFactor = glm::dot(-ray->GetDirection(), R);
            }
            //blinn-phong
            {
//                 glm::vec3 H = glm::normalize(-direction - ray->GetDirection());
//                 specularFactor = glm::dot(normal, H);  //���㵽��Դ ���㵽�ӵ� ��ƽ����
            }

            glm::vec3 specularColor = m_ks * light->m_color * glm::pow(glm::max(specularFactor, 0.f), m_shininess);

            glm::vec4 color(light->m_ambient * m_ka + diffuseColor + specularColor, m_d);
            //color = glm::clamp(color, glm::vec4(0.f, 0.f, 0.f, m_d), glm::vec4(1.f, 1.f, 1.f, m_d));
            return color;
        }

    private:
		glm::vec3 m_ka{ 0.f, 0.f, 0.f };	        //��Ӱɫ
		glm::vec3 m_kd{ 1.f, 1.f, 1.f };            //������
		glm::vec3 m_ks{ 1.f, 1.f, 1.f };            //�߹�
		float m_d{1.f};              //͸����
        float m_shininess{ 2.f };//�߹�ϵ��
    };

    /**
    ���̲���
    */
    class SimpleMaterial : public Material
    {
    public:
        SimpleMaterial(float scale, float reflectiveness = 0) : m_scale(scale), Material(reflectiveness) {}

        virtual glm::vec4 ray(std::shared_ptr<Ray> ray, std::shared_ptr<Light> light, glm::vec3 position, glm::vec3 normal)
        {
            return glm::abs((int)(glm::floor(position.x * 0.1f) + (int)glm::floor(position.z * m_scale)) % 2) < 1 ? glm::vec4{ 0.f, 0.f, 0.f, 1.f } : glm::vec4{ 1.f, 1.f, 1.f, 1.f };
        }

    private:
        float m_scale{};
    };
}

#endif