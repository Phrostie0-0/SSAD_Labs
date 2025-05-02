#include <bits/stdc++.h>

using namespace std;

class RecipeTemplate {
public:
    vector<string> ingredients;

    virtual void makeRecipe() final {
        listIngredients();
        prepareRecipe();
        serve();
    }

    void listIngredients() const {
        cout << "Ingredients:" << endl;
        for (const auto& item : ingredients) cout << "- " << item << endl;
    }

    virtual void prepareRecipe() const = 0;

    void serve() const {
        cout << "Serve the dish on a plate. Enjoy!" << endl;
    }

    virtual ~RecipeTemplate() = default;
};

class CakeRecipe : public RecipeTemplate {
public:
    CakeRecipe() {
        ingredients = {
                "2 cups flour",
                "1 cup sugar",
                "1/2 cup butter",
                "2 eggs",
                "1 tsp baking powder",
                "1/2 cup milk"
        };
    }

    void prepareRecipe() const override {
        cout << "Preparation steps for Cake:" << endl;
        cout << "1. Preheat oven to 175 degrees celsius." << endl;
        cout << "2. Cream butter and sugar until light and fluffy." << endl;
        cout << "3. Add eggs one at a time, beating well after each addition." << endl;
        cout << "4. Sift in flour and baking powder, mix gently." << endl;
        cout << "5. Stir in milk until smooth." << endl;
        cout << "6. Pour batter into a greased pan and bake for 30 minutes." << endl;
    }
};

class SaladRecipe : public RecipeTemplate {
public:
    SaladRecipe() {
        ingredients = {
                "2 cups mixed greens",
                "1 tomato, chopped",
                "1/2 cucumber, sliced",
                "1/4 cup feta cheese",
                "2 tbsp olive oil",
                "1 tbsp lemon juice",
                "Salt and pepper to taste"
        };
    }

    void prepareRecipe() const override {
        cout << "Preparation steps for Salad:" << endl;
        cout << "1. Wash and dry the greens." << endl;
        cout << "2. Combine greens, tomato, cucumber in a bowl." << endl;
        cout << "3. Sprinkle feta cheese on top." << endl;
        cout << "4. Drizzle olive oil and lemon juice." << endl;
        cout << "5. Toss gently to coat." << endl;
        cout << "6. Season with salt and pepper." << endl;
    }
};

int main() {
    vector<unique_ptr<RecipeTemplate>> recipes;
    recipes.emplace_back(make_unique<CakeRecipe>());
    recipes.emplace_back(make_unique<SaladRecipe>());

    for (const auto& recipe : recipes) {
        recipe->makeRecipe();
        cout << endl;
    }
}