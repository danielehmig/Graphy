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

		for (std::forward_list<int>::const_iterator it = list.mCostList.begin(); 
				it != list.mCostList.end(); it++)
		{
			mCostList.push_front(*it);
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
	void AdjList::addNode(const AdjListNode& node, int cost)
	{
		// Need to check if the node is already on the list
		if (exists(node))
		{
			// If it already is in the adjacency list, silently return
			return;
		}
		mAdjList.push_front(node);
		mCostList.push_front(cost);
		mNumEdges++;
	}

	/* ====================================================
		removeNode(AdjListNode)
	==================================================== */
	void AdjList::removeNode(const AdjListNode& node)
	{
		// If the list is empty, we don't need to remove anything
		if (mAdjList.empty())
		{
			return;
		}

		// First, check if the front is the node to remove
		if (mAdjList.front() == node)
		{
			mAdjList.pop_front();
			mCostList.pop_front();
			mNumEdges--;
		}
		else
		{
			std::forward_list<AdjListNode>::const_iterator prev = mAdjList.begin();
			std::forward_list<AdjListNode>::const_iterator it = prev++;

			// Also for the costs
			std::forward_list<int>::const_iterator costPrev = mCostList.begin();
			std::forward_list<int>::const_iterator costIt = costPrev++;
			while (it != mAdjList.end())
			{
				if (*it == node)
				{
					mAdjList.erase_after(prev);
					mCostList.erase_after(costPrev);
					mNumEdges--;
					break;
				}
				prev = it;
				it++;

				costPrev = costIt;
				costIt++;
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
		getCostList()
	==================================================== */
	std::forward_list<int> AdjList::getCostList() const
	{
		return mCostList;
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