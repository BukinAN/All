package mvc.Clinic.store;

import mvc.Clinic.models.clinic.Client;

import java.util.Collection;
import java.util.concurrent.ConcurrentHashMap;

public class ClientCash {
    private static final ClientCash INSTANCE = new ClientCash();

    private final ConcurrentHashMap<Integer, Client> clients = new ConcurrentHashMap<Integer, Client>();

    /**
     *
     * @return
     */
    public static ClientCash getInstance(){
        return INSTANCE;
    }

    /**
     *
     * @return
     */
    public Collection<Client> values(){
        return this.clients.values();
    }

    /**
     *
     * @param client
     */
    public void add(final Client client){
        this.clients.put(client.getId(), client);
    }

    /**
     *
     * @param client
     */
    public void edit(final Client client){
        this.clients.replace(client.getId(), client);
    }

    /**
     *
     * @param id
     */
    public void delete(final int id){
        this.clients.remove(id);
    }

    /**
     *
     * @param id
     * @return
     */
    public Client get(final int id){
        return this.clients.get(id);
    }
}
