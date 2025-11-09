import numpy as np

# Objective Function: Rosenbrock Function
def rosenbrock(position):
    return np.sum(position**2)


# Particle Swarm Optimizer (PSO)
class ParticleSwarmOptimizer:
    def __init__(self, obj_func, dim, bounds, n_particles=30, max_iter=100, w=0.7, c1=1.5, c2=1.5):
        self.obj_func = obj_func
        self.dim = dim
        self.bounds = bounds
        self.n_particles = n_particles
        self.max_iter = max_iter
        
        # Parameters
        self.w = w        # inertia weight
        self.c1 = c1      # cognitive coefficient
        self.c2 = c2      # social coefficient
        
        # Initialize particles
        self.positions = np.random.uniform(bounds[0], bounds[1], (n_particles, dim))
        self.velocities = np.random.uniform(-1, 1, (n_particles, dim))
        
        # Initialize personal and global bests
        self.pbest_positions = self.positions.copy()
        self.pbest_scores = np.array([float('inf')] * n_particles)
        self.gbest_position = np.zeros(dim)
        self.gbest_score = float('inf')

    def optimize(self):
        for iteration in range(self.max_iter):
            for i in range(self.n_particles):
                # Keep particle within bounds
                self.positions[i] = np.clip(self.positions[i], self.bounds[0], self.bounds[1])
                
                # Evaluate fitness
                fitness = self.obj_func(self.positions[i])
                
                # Update personal best
                if fitness < self.pbest_scores[i]:
                    self.pbest_scores[i] = fitness
                    self.pbest_positions[i] = self.positions[i].copy()
                    
                # Update global best
                if fitness < self.gbest_score:
                    self.gbest_score = fitness
                    self.gbest_position = self.positions[i].copy()
            
            # Update inertia weight (optional linear decay)
            w = self.w - (self.w - 0.4) * (iteration / self.max_iter)
            
            # Update velocity and position
            for i in range(self.n_particles):
                r1, r2 = np.random.rand(self.dim), np.random.rand(self.dim)
                cognitive = self.c1 * r1 * (self.pbest_positions[i] - self.positions[i])
                social = self.c2 * r2 * (self.gbest_position - self.positions[i])
                self.velocities[i] = w * self.velocities[i] + cognitive + social
                
                # Update positions
                self.positions[i] += self.velocities[i]
            
            print(f"Iteration {iteration+1}/{self.max_iter}, Best Fitness: {self.gbest_score:.6f}")
        
        return self.gbest_position, self.gbest_score


# Main Function
if __name__ == "__main__":
    dim = 5          # Number of dimensions
    bounds = (-10, 10)    # Search space
    pso = ParticleSwarmOptimizer(rosenbrock, dim, bounds, n_particles=400, max_iter=500)
    
    best_position, best_score = pso.optimize()
    
    print("\nBest Position:", best_position)
    print("Best (Global) Fitness:", best_score)  