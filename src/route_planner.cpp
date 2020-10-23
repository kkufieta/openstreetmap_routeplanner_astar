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

// Return the final path found from A* search.
// The parameter current_node is the last node in the path.
std::vector<RouteModel::Node>
RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
  // Create path_found vector
  distance = current_node->g_value;
  std::vector<RouteModel::Node> path_found;

  while (current_node != this->start_node) {
    path_found.emplace_back(*current_node);
    current_node = current_node->parent;
  }
  path_found.emplace_back(*this->start_node);

  std::reverse(path_found.begin(), path_found.end());

  distance *= m_Model.MetricScale(); // Multiply the distance by the scale
                                     // of the map to get meters.
  return path_found;
}

// A* Search algorithm
void RoutePlanner::AStarSearch() {
  RouteModel::Node *current_node = nullptr;
  this->open_list.emplace_back(this->start_node);
  this->start_node->visited = true;
  while (!(open_list.empty())) {
    // Get the next node by sorting open_list and returning the node
    // with the smallest f = g + h value
    current_node = this->NextNode();
    if (current_node == this->end_node) {
      // Save the final path in the RouteModel
      m_Model.path = this->ConstructFinalPath(current_node);
      std::cout << "Total Distance: " << this->GetDistance() << "\n";
    }
    // Add all neighbors of the current node to the open_list.
    this->AddNeighbors(current_node);
  }
}