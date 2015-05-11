#include "AdjList.h"

namespace Graphy_Graph
{

	/* ====================================================
		AdjList()
	==================================================== */
	AdjList::AdjList()
	{
	}

	/* ====================================================
		AdjList(AdjListNode)
	==================================================== */
	AdjList::AdjList(const AdjListNode& node)
	{
		mNode = node;
	}

	/* ====================================================
	AdjList(AdjList)
	==================================================== */
	AdjList::AdjList(const AdjList& list)
	{
		mNode = list.getNode();
		mNumEdges = list.numEdges();
		for (std::forward_list<AdjListNode>::const_iterator it = list.mAdjList.begin();
				it != list.mAdjList.end(); it++)
		{
			mAdjList.push_front(*it);
		}
	}

	/* ====================================================
		empty()
	==================================================== */
	bool AdjList::empty() const
	{
		return (mNumEdges == 0);
	}

	/* ====================================================
		addNode(AdjListNode)
	==================================================== */
	void AdjList::addNode(const AdjListNode& node)
	{
		// Need to check if the node is already on the list
		if (exists(node))
		{
			// If it already is in the adjacency list, silently return
			return;
		}
		mAdjList.push_front(node);
		mNumEdges++;
	}

	/* ====================================================
		removeNode(AdjListNode)
	==================================================== */
	void AdjList::removeNode(const AdjListNode& node)
	{
		// First, check if the front is the node to remove
		if (mAdjList.front() == node)
		{
			mAdjList.pop_front();
			mNumEdges--;
		}
		else
		{
			std::forward_list<AdjListNode>::const_iterator prev = mAdjList.begin();
			std::forward_list<AdjListNode>::const_iterator it = prev++;
			while (it != mAdjList.end())
			{
				if (*it == node)
				{
					mAdjList.erase_after(it);
					mNumEdges--;
					break;
				}
				prev = it;
				it++;
			}
		}
	}

	AdjListNode AdjList::front() const
	{
		return mAdjList.front();
	}

	/* ====================================================
		exists(AdjListNode)
	==================================================== */
	bool AdjList::exists(const AdjListNode& node) const
	{
		for (std::forward_list<AdjListNode>::const_iterator it = mAdjList.begin();
			it != mAdjList.end(); it++)
		{
			// We (allegedly) overrode the == operator for AdjListNode
			if (*it == node)
			{
				return true;
			}
		}

		// We never found it
		return false;
	}

	/* ====================================================
		getNode()
	==================================================== */
	AdjListNode AdjList::getNode() const
	{
		return mNode;
	}

	/* ====================================================
		numEdges()
	==================================================== */
	int AdjList::numEdges() const
	{
		return mNumEdges;
	}
}