#ifndef _RIVE_KEY_FRAME_COLOR_BASE_HPP_
#define _RIVE_KEY_FRAME_COLOR_BASE_HPP_
#include "animation/keyframe.hpp"
#include "core/field_types/core_color_type.hpp"
namespace rive
{
	class KeyFrameColorBase : public KeyFrame
	{
	public:
		static const int typeKey = 37;

		// Helper to quickly determine if a core object extends another without RTTI
		/// at runtime.
		bool isTypeOf(int typeKey) override
		{
			switch (typeKey)
			{
				case KeyFrameColorBase::typeKey:
				case KeyFrameBase::typeKey:
					return true;
				default:
					return false;
			}
		}

		int coreType() const override { return typeKey; }

		static const int valuePropertyKey = 88;

	private:
		int m_Value = 0;
	public:
		int value() const { return m_Value; }
		void value(int value)
		{
			if (m_Value == value)
			{
				return;
			}
			m_Value = value;
			valueChanged();
		}

		bool deserialize(int propertyKey, BinaryReader& reader) override
		{
			switch (propertyKey)
			{
				case valuePropertyKey:
					m_Value = CoreColorType::deserialize(reader);
					return true;
			}
			return KeyFrame::deserialize(propertyKey, reader);
		}

	protected:
		virtual void valueChanged() {}
	};
} // namespace rive

#endif