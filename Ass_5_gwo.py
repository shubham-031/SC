import numpy as np

# Define the objective function (Sphere function)
def rosenbrock(position):
    a = 1.0
    b = 100.0
    # Works for n-dimensional input
    return np.sum((a - position[:-1])**2 + b * (position[1:] - position[:-1]**2)**2)

# Grey Wolf Optimizer
class GreyWolfOptimizer:
    def __init__(self, obj_func, dim, bounds, n_wolves=20, max_iter=100):
        self.obj_func = obj_func
        self.dim = dim
        self.bounds = bounds
        self.n_wolves = n_wolves
        self.max_iter = max_iter
        
        # Initialize wolves randomly within bounds
        self.positions = np.random.uniform(bounds[0], bounds[1], (n_wolves, dim))
        
        # Initialize alpha, beta, delta wolves
        self.alpha_pos = np.zeros(dim)
        self.beta_pos = np.zeros(dim)
        self.delta_pos = np.zeros(dim)
        
        self.alpha_score = float("inf")
        self.beta_score = float("inf")
        self.delta_score = float("inf")

    def optimize(self):
        for iteration in range(self.max_iter):
            for i in range(self.n_wolves):
                # Ensure wolves stay within bounds
                self.positions[i] = np.clip(self.positions[i], self.bounds[0], self.bounds[1])
                
                # Evaluate fitness
                fitness = self.obj_func(self.positions[i])
                
                # Update alpha, beta, delta wolves
                if fitness < self.alpha_score:
                    self.delta_score = self.beta_score
                    self.delta_pos = self.beta_pos.copy()
                    
                    self.beta_score = self.alpha_score
                    self.beta_pos = self.alpha_pos.copy()
                    
                    self.alpha_score = fitness
                    self.alpha_pos = self.positions[i].copy()
                
                elif fitness < self.beta_score:
                    self.delta_score = self.beta_score
                    self.delta_pos = self.beta_pos.copy()
                    
                    self.beta_score = fitness
                    self.beta_pos = self.positions[i].copy()
                
                elif fitness < self.delta_score:
                    self.delta_score = fitness
                    self.delta_pos = self.positions[i].copy()
            
            # Parameter 'a' decreases linearly from 2 to 0
            a = 2 - iteration * (2 / self.max_iter)
            
            # Update positions of wolves
            for i in range(self.n_wolves):
                for d in range(self.dim):
                    r1, r2 = np.random.rand(), np.random.rand()
                    A1 = 2 * a * r1 - a
                    C1 = 2 * r2
                    D_alpha = abs(C1 * self.alpha_pos[d] - self.positions[i][d])
                    X1 = self.alpha_pos[d] - A1 * D_alpha
                    
                    r1, r2 = np.random.rand(), np.random.rand()
                    A2 = 2 * a * r1 - a
                    C2 = 2 * r2
                    D_beta = abs(C2 * self.beta_pos[d] - self.positions[i][d])
                    X2 = self.beta_pos[d] - A2 * D_beta
                    
                    r1, r2 = np.random.rand(), np.random.rand()
                    A3 = 2 * a * r1 - a
                    C3 = 2 * r2
                    D_delta = abs(C3 * self.delta_pos[d] - self.positions[i][d])  
                    X3 = self.delta_pos[d] - A3 * D_delta
                    
                    # Final update
                    self.positions[i][d] = (X1 + X2 + X3) / 3.0
            
            print(f"Iteration {iteration+1}/{self.max_iter}, Best Fitness: {self.alpha_score:.6f}")
        
        return self.alpha_pos, self.alpha_score ,self.beta_score ,self.delta_score


# Main function
if __name__ == "__main__":
    dim = 5                # Number of dimensions
    bounds = (-10, 10)     # Search space
    gwo = GreyWolfOptimizer(rosenbrock, dim, bounds, n_wolves=20, max_iter=50)
    best_position, a_score , b_score , d_score = gwo.optimize()
    
    print("\nBest Position:", best_position)
    print("Alpha Score:", a_score)
    print("Beta Score:", b_score)
    print("Delta Score:", d_score)