package mvc.Clinic.models.clinic.animals;


public abstract class Pet {

    protected String name;

    /**
     * конструктор
     * @param name им€ питомца
     */
    public Pet(String name) {
        this.name = name;
    }

    /**
     *
     * @param name им€ питомца
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     *
     * @return возвращ€ет им€ питомца
     */
    public String getName() {
        return this.name;
    }

    /**
     *
     * @return строковое представление класса Pet
     */
    @Override
    public String toString() {
        return this.getClass().getSimpleName() + "{" +
                "name='" + name + '\'' +
                '}';
    }
}