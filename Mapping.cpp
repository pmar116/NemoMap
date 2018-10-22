#include "Mapping.h"


ParaMODAImpl::Mapping::Mapping()
{
   this->Id = -1;
}

ParaMODAImpl::Mapping::Mapping(const Mapping & mapping)
{
   this->Id = mapping.Id;
   this->SubGraphEdgeCount = mapping.SubGraphEdgeCount;
   this->Function = mapping.Function;
}


ParaMODAImpl::Mapping::Mapping(tsl::hopscotch_map<int, int> function)
{
   this->Id = -1;
   this->Function = function;
}

ParaMODAImpl::Mapping::~Mapping()
{
}




////NEED FURTHER CHECK for correct quickgraph integration
//QuickGraph::Edge<int>^ ParaMODAImpl::Mapping::GetImage(QuickGraph::UndirectedGraph<int>^ inputGraph, QuickGraph::Edge<int>^ newlyAddedEdge)
//{
//   QuickGraph::Edge<int>% image = QuickGraph::Edge<int>();
//   int source = (int)(newlyAddedEdge->Source);
//   int target = (int)(newlyAddedEdge->Target);
//   try
//   {
//	  if (inputGraph->TryGetEdge(this->Function.at(source), this->Function.at(target), image))
//		 return image;
//   }
//   catch (out_of_range) {}
//   return QuickGraph::Edge<int>(DefaultEdgeNodeVal, DefaultEdgeNodeVal);
//}




//Overload equal operator for comparing Mapping objects
//	  all <key,value> pairs must be the same in both objects
bool ParaMODAImpl::Mapping::operator==(const Mapping & other) const
{
   if (this->Id >= 0 || other.Id >= 0)
	  return this->Id == other.Id;

   if (this->Function.size() != other.Function.size())
	  return false;

   for (auto const& itr : this->Function)
   {
	   try
	   {
		   if (itr.second != other.getFunction().at(itr.first))
			   return false;
	   }
	   catch (out_of_range)
	   {
		   return false;
	   }
   }
   return true;
}



string ParaMODAImpl::Mapping::GetMappedNodes()
{
   string result = "";
   if (this->Function.size())
   {
	   tsl::hopscotch_map<int, int>::iterator itr = this->Function.begin();
	  result += to_string((itr++)->second);
	  for (; itr != this->Function.end(); itr++)
	  {
		 result += '-' + to_string(itr->second);
	  }
   }
   return result;
}


//overload output operators
ostream & ParaMODAImpl::operator<<(ostream & outStream, const Mapping & data)
{
   string h = "";
   string g = "";

   if (data.getFunction().size())
   {
	  h += "[";
	  g += " => [";

	  for (auto const& itr : data.getFunction())
	  {
		 h += to_string(itr.first) + '-';
		 g += to_string(itr.second) + '-';
	  }
	  h.pop_back();
	  h += "]";
	  g.pop_back();
	  g += "]\n";
   }
   outStream << h << g;
   return outStream;
}
