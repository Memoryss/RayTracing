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

        //照射
        virtual glm::vec4 ray(std::shared_ptr<Ray> ray, std::shared_ptr<Light> light, glm::vec3 position, glm::vec3 normal) = 0;

        float GetReflectiveness() { return m_reflectiveness; }

    private:
        float m_reflectiveness{};       //反射度属性  0表示不反射 光线全被吸收

    };

    /**
    blinn-phong模型材质
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
                //计算反射光线
                glm::vec3 R = glm::normalize(direction - normal *(glm::dot(normal, direction) * 2));
                specularFactor = glm::dot(-ray->GetDirection(), R);
            }
            //blinn-phong
            {
//                 glm::vec3 H = glm::normalize(-direction - ray->GetDirection());
//                 specularFactor = glm::dot(normal, H);  //顶点到光源 顶点到视点 角平分线
            }

            glm::vec3 specularColor = m_ks * light->m_color * glm::pow(glm::max(specularFactor, 0.f), m_shininess);

            glm::vec4 color(light->m_ambient * m_ka + diffuseColor + specularColor, m_d);
            //color = glm::clamp(color, glm::vec4(0.f, 0.f, 0.f, m_d), glm::vec4(1.f, 1.f, 1.f, m_d));
            return color;
        }

    private:
		glm::vec3 m_ka{ 0.f, 0.f, 0.f };	        //阴影色
		glm::vec3 m_kd{ 1.f, 1.f, 1.f };            //漫反射
		glm::vec3 m_ks{ 1.f, 1.f, 1.f };            //高光
		float m_d{1.f};              //透明度
        float m_shininess{ 2.f };//高光系数
    };

    /**
    棋盘材质
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

    /**
    pbr材质模型
    */
    class PBRMaterial : public Material
    {

    public:
        virtual glm::vec4 ray(std::shared_ptr<Ray> ray, std::shared_ptr<Light> light, glm::vec3 position, glm::vec3 normal) override
        {
            static const float PI = 3.14159265359f;

            glm::vec3 N = glm::normalize(normal);
            glm::vec3 L = glm::normalize(-light->GetDirection(position));
            glm::vec3 V = glm::normalize(-ray->GetDirection());
            glm::vec3 H = glm::normalize(V + L);
            glm::vec3 F0(0.04f);
            F0 = glm::mix(F0, m_albedo, m_metallic);

            glm::vec3 Lo(0.f);

            glm::vec3 radiance = light->m_color;

            float NDF = distributionGGX(N, H, m_roughness);
            float G = GeometrySmith(N, V, L, m_roughness);
            glm::vec3 F = fresnelSchlick(glm::clamp(dot(H, V), 0.f, 1.f), F0);

            glm::vec3 nominator = NDF * G * F;
            float denominator = 4 * glm::max(glm::dot(N, V), 0.f) * glm::max(glm::dot(N, L), 0.f);
            glm::vec3 specular = nominator / glm::max(denominator, 0.001f);

            glm::vec3 kS = F;
            glm::vec3 kD = glm::vec3(1.f) - kS;
            kD *= 1.0 - m_metallic;

            float NdotL = glm::max(glm::dot(N, L), 0.f);

            Lo += (kD * m_albedo / PI + specular) * radiance * NdotL;

            glm::vec3 ambient = glm::vec3(0.03f) * m_albedo * m_ao;

            glm::vec3 color = ambient + Lo;

            color = color / (color + glm::vec3(1.f));
            color = pow(color, glm::vec3(1.f / 2.2f));

            return glm::vec4(color, 1.f);
        }

    protected:
        float distributionGGX(glm::vec3 N, glm::vec3 H, float roughness)
        {
            static const float PI = 3.14159265359f;

            float a = roughness * roughness;
            float a2 = a * a;
            float NdotH = glm::max(glm::dot(N, H), 0.f);
            float NdotH2 = NdotH * NdotH;

            float nom = a2;
            float denom = (NdotH2 * (a2 - 1.0f) + 1.0f);
            denom = PI * denom * denom;

            return nom / glm::max(denom, 0.001f);
        }

        float geometrySchlickGGX(float NdotV, float roughness)
        {
            float r = (roughness + 1.0f);
            float k = (r * r) / 8.f;

            float nom = NdotV;
            float denom = NdotV * (1.f - k) + k;

            return nom / denom;
        }

        float GeometrySmith(glm::vec3 N, glm::vec3 V, glm::vec3 L, float roughtness)
        {
            float NdotV = glm::max(dot(N, V), 0.f);
            float NdotL = glm::max(dot(N, L), 0.f);
            float ggx2 = geometrySchlickGGX(NdotV, roughtness);
            float ggx1 = geometrySchlickGGX(NdotL, roughtness);

            return ggx1 * ggx2;
        }

        glm::vec3 fresnelSchlick(float cosTheta, glm::vec3 F0)
        {
            return F0 + (1.f - F0) * glm::pow(1.f - cosTheta, 5.f);
        }

    private:
        glm::vec3 m_albedo;     //反射率
        float m_metallic;       //金属度
        float m_roughness;      //粗糙度
        float m_ao;             //...
    };
}

#endif