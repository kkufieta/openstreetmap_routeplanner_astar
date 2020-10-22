#include "route_planner.h"
#include "route_model.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y,
                           float end_x, float end_y)
    : m_Model(model) {
  // Convert inputs to percentage:
  start_x *= 0.01;
  start_y *= 0.01;
  end_x *= 0.01;
  end_y *= 0.01;

  // Find the closest nodes to the starting and ending coordinates.
  // Store the nodes you find in the RoutePlanner's start_node and
  // end_node attributes.
  start_node = &m_Model.FindClosestNode(start_x, start_y);
  end_node = &m_Model.FindClosestNode(end_x, end_y);
}

// Return the distance from node to the end_node.
float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
  return node->distance(*(this->end_node));
}

// Add unvisited neighbors of the current node to the open_list.
void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
  // Find and save the neighbors for the current node
  current_node->FindNeighbors();
  // Push the neighbors that aren't visited yet to the open_list
  for (RouteModel::Node *neighbor : current_node->neighbors) {
    if (!(neighbor->visited)) {
      // Calculate and set the g_value and h_value
      neighbor->h_value = this->CalculateHValue(neighbor);
      neighbor->g_value =
          current_node->g_value + current_node->distance(*neighbor);
      // Set the parent to the current node, and visited to true
      neighbor->parent = current_node;
      neighbor->visited = true;
      // Add the neighbor to the open list
      this->open_list.emplace_back(neighbor);
    }
  }
}

// Sort the open_list and return the next node.
RouteModel::Node *RoutePlanner::NextNode() {
  // Sort open_list using a lambda expression
  std::sort(this->open_list.begin(), this->open_list.end(),
            [](RouteModel::Node *node_1, RouteModel::Node *node_2) {
              return (node_1->g_value + node_1->h_value) >
                     (node_2->g_value + node_2->h_value);
            });
  RouteModel::Node *next_node = this->open_list.back();
  this->open_list.pop_back();
  return next_node;
}

// TODO 6: Complete the ConstructFinalPath method to return the final path found
// from your A* search. Tips:
// - This method should take the current (final) node as an argument and
// iteratively follow the
//   chain of parents of nodes until the starting node is found.
// - For each node in the chain, add the distance from the node to its parent to
// the distance variable.
// - The returned vector should be in the correct order: the start node should
// be the first element
//   of the vector, the end node should be the last element.

std::vector<RouteModel::Node>
RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
  // Create path_found vector
  distance = 0.0f;
  std::vector<RouteModel::Node> path_found;

  // TODO: Implement your solution here.

  distance *= m_Model.MetricScale(); // Multiply the distance by the scale of
                                     // the map to get meters.
  return path_found;
}

// TODO 7: Write the A* Search algorithm here.
// Tips:
// - Use the AddNeighbors method to add all of the neighbors of the current node
// to the open_list.
// - Use the NextNode() method to sort the open_list and return the next node.
// - When the search has reached the end_node, use the ConstructFinalPath method
// to return the final path that was found.
// - Store the final path in the m_Model.path attribute before the method exits.
// This path will then be displayed on the map tile.

void RoutePlanner::AStarSearch() {
  RouteModel::Node *current_node = nullptr;

  // TODO: Implement your solution here.
}