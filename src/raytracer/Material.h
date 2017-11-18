#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <memory>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/detail/func_geometric.hpp>
#include <glm/detail/func_common.hpp>
#include "Ray.h"
#include "Light.h"

namespace RayTracing
{
    class Material
    {
    public:
        //����
        virtual glm::vec4 ray(std::shared_ptr<Ray> ray, std::shared_ptr<Light> light, glm::vec3 position, glm::vec3 normal) = 0;
    };

    /**
    blinn-phongģ�Ͳ���
    */
    class PhongMaterial : public Material
    {
    public:
		PhongMaterial(const glm::vec3 &kd, const glm::vec3 &ks, float shininess)
			: m_kd(kd), m_ks(ks), m_shininess(shininess)
		{

		}

        virtual glm::vec4 ray(std::shared_ptr<Ray> ray, std::shared_ptr<Light> light, glm::vec3 position, glm::vec3 normal) override
        {
            normal = glm::normalize(normal);
            auto direction = glm::normalize(light->GetDirection(position));

            float diffuseFactor = glm::max(0.f, dot(normal, direction));
            glm::vec3 diffuseColor = m_kd * diffuseFactor * light->m_color;
            glm::vec3 H = glm::normalize((-direction) + (-ray->GetDirection()));  //���㵽��Դ ���㵽�ӵ� ��ƽ����
            glm::vec3 specularColor = m_ks * light->m_color * std::pow(glm::max(0.f, glm::dot(H, normal)), m_shininess);

            return glm::vec4(light->m_ambient * m_ka + diffuseColor + specularColor, m_d);
        }

    private:
		glm::vec3 m_ka{ 0.f, 0.f, 0.f, 1.f };	      //��Ӱɫ
		glm::vec3 m_kd{ 1.f, 1.f, 1.f, 1.f };         //������
		glm::vec3 m_ks{ 1.f, 1.f, 1.f, 1.f };         //�߹�
		float m_d{1.f};              //͸����
        float m_shininess{ 2.f };//�߹�ϵ��
    };

    /**
    ���̲���
    */
    class SimpleMaterial : public Material
    {
    public:
        SimpleMaterial(float scale) : m_scale(scale) {}

        virtual glm::vec4 ray(std::shared_ptr<Ray> ray, std::shared_ptr<Light> light, glm::vec3 position, glm::vec3 normal)
        {
            return glm::abs((glm::floor(position.x * 0.1f) + glm::floor(position.z * m_scale)) % 2) < 1 ? glm::vec4{ 0.f, 0.f, 0.f, 255.f } : glm::vec4{ 255.f, 255.f, 255.f, 255.f };
        }

    private:
        float m_scale{};
    };
}

#endif