#ifndef _RIVE_LINEAR_GRADIENT_BASE_HPP_
#define _RIVE_LINEAR_GRADIENT_BASE_HPP_
#include "container_component.hpp"
#include "core/field_types/core_double_type.hpp"
namespace rive
{
	class LinearGradientBase : public ContainerComponent
	{
	public:
		static const int typeKey = 22;

		// Helper to quickly determine if a core object extends another without RTTI
		/// at runtime.
		bool isTypeOf(int typeKey) override
		{
			switch (typeKey)
			{
				case LinearGradientBase::typeKey:
				case ContainerComponentBase::typeKey:
				case ComponentBase::typeKey:
					return true;
				default:
					return false;
			}
		}

		int coreType() const override { return typeKey; }

		static const int startXPropertyKey = 42;
		static const int startYPropertyKey = 33;
		static const int endXPropertyKey = 34;
		static const int endYPropertyKey = 35;
		static const int opacityPropertyKey = 46;

	private:
		double m_StartX = 0;
		double m_StartY = 0;
		double m_EndX = 0;
		double m_EndY = 0;
		double m_Opacity = 1;
	public:
		double startX() const { return m_StartX; }
		void startX(double value)
		{
			if (m_StartX == value)
			{
				return;
			}
			m_StartX = value;
			startXChanged();
		}

		double startY() const { return m_StartY; }
		void startY(double value)
		{
			if (m_StartY == value)
			{
				return;
			}
			m_StartY = value;
			startYChanged();
		}

		double endX() const { return m_EndX; }
		void endX(double value)
		{
			if (m_EndX == value)
			{
				return;
			}
			m_EndX = value;
			endXChanged();
		}

		double endY() const { return m_EndY; }
		void endY(double value)
		{
			if (m_EndY == value)
			{
				return;
			}
			m_EndY = value;
			endYChanged();
		}

		double opacity() const { return m_Opacity; }
		void opacity(double value)
		{
			if (m_Opacity == value)
			{
				return;
			}
			m_Opacity = value;
			opacityChanged();
		}

		bool deserialize(int propertyKey, BinaryReader& reader) override
		{
			switch (propertyKey)
			{
				case startXPropertyKey:
					m_StartX = CoreDoubleType::deserialize(reader);
					return true;
				case startYPropertyKey:
					m_StartY = CoreDoubleType::deserialize(reader);
					return true;
				case endXPropertyKey:
					m_EndX = CoreDoubleType::deserialize(reader);
					return true;
				case endYPropertyKey:
					m_EndY = CoreDoubleType::deserialize(reader);
					return true;
				case opacityPropertyKey:
					m_Opacity = CoreDoubleType::deserialize(reader);
					return true;
			}
			return ContainerComponent::deserialize(propertyKey, reader);
		}

	protected:
		virtual void startXChanged() {}
		virtual void startYChanged() {}
		virtual void endXChanged() {}
		virtual void endYChanged() {}
		virtual void opacityChanged() {}
	};
} // namespace rive

#endif