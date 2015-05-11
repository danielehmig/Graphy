#include "AdjListNode.h"

/* ========================================================
	Implementation of CLASS AdjListNode
======================================================== */

namespace Graphy_Graph
{
	/* ====================================================
		AdjListNode()
	==================================================== */
	AdjListNode::AdjListNode()
	{
	}

	/* ====================================================
		AdjListNode(string, int)
	==================================================== */
	AdjListNode::AdjListNode(const std::string& s, const int index)
	{
		mLabel = s;
		mIndex = index;
	}

	/* ====================================================
	AdjListNode(AdjListNode)
	==================================================== */
	AdjListNode::AdjListNode(const AdjListNode& node)
	{
		mLabel = node.mLabel;
		mIndex = node.mIndex;
	}

	/* ====================================================
		setLabel(string)
	==================================================== */
	void AdjListNode::setLabel(const std::string& s)
	{
		mLabel = s;
	}

	/* ====================================================
		getLabel()
	==================================================== */
	std::string AdjListNode::getLabel() const
	{
		return mLabel;
	}

	/* ====================================================
		setIndex(int)
	==================================================== */
	void AdjListNode::setIndex(const int index)
	{
		mIndex = index;
	}

	/* ====================================================
		getIndex()
	==================================================== */
	int AdjListNode::getIndex() const
	{
		return mIndex;
	}

	/* ====================================================
		operator ==
	==================================================== */
	bool AdjListNode::operator ==(const AdjListNode& other) const
	{
		if (mLabel == other.mLabel)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	/* ====================================================
		operator !=
	==================================================== */
	bool AdjListNode::operator !=(const AdjListNode& other) const
	{
		return !(*this == other);
	}
}