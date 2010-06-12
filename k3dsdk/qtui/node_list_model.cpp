// K-3D
// Copyright (c) 1995-2010, Timothy M. Shead
//
// Contact: tshead@k-3d.com
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

/** \file
	\author Tim Shead (tshead@k-3d.com)
*/

#include <k3dsdk/inode.h>
#include <k3dsdk/qtui/convert.h>
#include <k3dsdk/qtui/node_list_model.h>

namespace k3d
{

namespace qtui
{

/////////////////////////////////////////////////////////////////////////////
// node_list_model

node_list_model::node_list_model(QObject* Parent) :
	base(Parent)
{
}

node_list_model::~node_list_model()
{
}

void node_list_model::add_nodes(const std::vector<inode*>& Nodes)
{
	for(uint_t i = 0; i != Nodes.size(); ++i)
		nodes.erase(std::remove(nodes.begin(), nodes.end(), Nodes[i]), nodes.end());
	nodes.insert(nodes.end(), Nodes.begin(), Nodes.end());
	nodes.erase(std::remove(nodes.begin(), nodes.end(), static_cast<inode*>(0)), nodes.end());
	reset();
}

void node_list_model::remove_nodes(const std::vector<inode*>& Nodes)
{
	for(uint_t i = 0; i != Nodes.size(); ++i)
		nodes.erase(std::remove(nodes.begin(), nodes.end(), Nodes[i]), nodes.end());
	reset();
}

int node_list_model::rowCount(const QModelIndex& parent) const
{
	return nodes.size();
}

QVariant node_list_model::data(const QModelIndex& index, int role) const
{
	if(index.isValid() && index.row() < nodes.size())
	{
		switch(role)
		{
			case Qt::DisplayRole:
			{
				return convert<QString>(nodes[index.row()]->name());
			}
			default:
			{
				break;
			}
		}
	}
	
	return QVariant();
}

} // namespace qtui

} // namespace k3d

