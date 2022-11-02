package test.inherit;

public class Inherit {
    public void rest() {
        System.out.println("休息!");
    }

    @Override
    public boolean equals(Object obj) {
        if (obj == null) {
            return false;
        }else {
            if (obj instanceof Inherit) {
                Inherit i = (Inherit) obj;
                if (i.name.equals(this.name) && i.height == this.height) {
                    return true;
                }
            }
            return false;
        }
    }
    @Override
    public String toString() {
        return this.name + "'s height is " + height;
    }

    String name;
    int height;
}

