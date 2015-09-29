package mvc.Clinic.models.clinic;

import mvc.Clinic.models.clinic.animals.Pet;

import java.util.Iterator;
import java.util.LinkedList;

public class Clinic {


    private static  final Clinic INSTANCE = new Clinic();
    private final LinkedList<Client> clients = new LinkedList<Client>();


    private Clinic() {
    }

    /**
     *
     * @return возвращает объект клиники
     */
    public static Clinic getInstance() {
        return INSTANCE;
    }

    /**
     *
     * @return возвращает список клиентов клиники
     */
    public LinkedList<Client> getClients() {
        return clients;
    }

    /**
     *
     * @param index индекс клиента
     * @return возвращает клиента по индексу
     */
    public Client getClient(int index) {
        return clients.get(index-1);
    }

    /**
     *
     * @param client добавляет клиента
     */
    public void addClient(final Client client) {
        this.clients.addLast(client);
    }


    /**
     *
     * @param name изменение клиента по имени
     */
    public void removeClientByName(final String name) {
        int j = 0;
        for (Iterator<Client> it = clients.iterator(); it.hasNext(); ) {
            if (it.next().getName().equals(name)) {
                it.remove();
                j = j + 1;
            }
        }
        if (j != 0) {
            System.out.println("The client " + name + " has removed successfully");
        } else {
            System.out.println("This client doesn't exist in the base");
        }
    }

    /**
     *
     * @param id удаление клиента по идентификатору
     */
    public void removeClientById(final int id){
        clients.remove(id);
    }

    /**
     *
     * @param name имя питомца
     * @return возвращает клиента по питомцу
     */
    public LinkedList<Client> findClientsByPetName(final String name) {
        LinkedList<Client> foundedClients = new LinkedList<Client>();
        int i = 0;
        for (Client client : clients) {
            if (client != null && client.getPet().getName().equals(name)) {
                foundedClients.addLast(client);
                i++;
            }
        }
        return foundedClients;
    }

    /**
     * Выводит на печать список клиентов по имени питомца
     * @param name имя митомца
     */
    public void printClientsByPetName(final String name) {
        LinkedList<Client> foundedClients = findClientsByPetName(name);
        int j = 0;
        for (Client client : foundedClients) {
            if (client != null) {
                System.out.println(client.getId());
                j = j + 1;
            }
        }
        if (j == 0) {
            System.out.println("Client with that pet's name didn't find");
        }
    }

    /**
     *
     * @param client клиент
     * @return возвращает питомца по клиенту
     */
    public LinkedList<Pet> findPetsByClient(final String client) {
       LinkedList<Pet> foundedPets = new LinkedList<Pet>();
        int i = 0;
        for (Client clientId : clients) {
            if (clientId != null && clientId.getName().equals(client)) {
                foundedPets.addLast(clientId.getPet());
                i++;
            }
        }
        return foundedPets;
    }

    /**
     *
     * @param name имя клиента
     * @return возвращает клиента
     */
    public LinkedList<Client> findClient(final String name){
        LinkedList<Client> foundedClients = new LinkedList<Client>();
        for (Client client : clients){
            if (client != null && client.getName().equals(name)){
                foundedClients.addLast(client);
            }
        }
        return foundedClients;
    }

    /**
     * печать списка питомцев по клиенту
     * @param client клиент
     */
    public void printPetsByClient(final String client) {
        LinkedList<Pet> foundedPets = findPetsByClient(client);
        int j = 0;
        for (Pet pet : foundedPets) {
            if (pet != null) {
                System.out.println(pet.getName() + "   " + pet.getClass().getSimpleName());
                j = j + 1;
            }
        }
        if (j == 0) {
            System.out.println("Client with that pet's name didn't find");
        }
    }

    /**
     * печать всех клиентов
     */
    public void printAllClients() {
        for (Client client : clients) {
            System.out.println(client.getId() + " - " + client.getPet().getName());
        }
    }
}