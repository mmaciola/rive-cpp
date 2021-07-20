#ifndef _RIVE_I_KCONSTRAINT_HPP_
#define _RIVE_I_KCONSTRAINT_HPP_
#include "generated/constraints/ik_constraint_base.hpp"
#include "math/mat2d.hpp"
#include "math/transform_components.hpp"
#include <stdio.h>
#include <vector>

namespace rive
{
	class Bone;
	class IKConstraint : public IKConstraintBase
	{
	private:
		struct BoneChainLink
		{
			int index;
			Bone* bone;
			float angle;
			TransformComponents transformComponents;
			Mat2D parentWorldInverse;
		};
		std::vector<BoneChainLink> m_FkChain;
		void solve1(BoneChainLink* fk1, const Vec2D& worldTargetTranslation);
		void solve2(BoneChainLink* fk1,
		            BoneChainLink* fk2,
		            const Vec2D& worldTargetTranslation);
		void constrainRotation(BoneChainLink& fk, float rotation);

	public:
		void markConstraintDirty() override;
		StatusCode onAddedClean(CoreContext* context) override;
		void buildDependencies() override;
		void constrain(TransformComponent* component) override;
	};
} // namespace rive

#endif