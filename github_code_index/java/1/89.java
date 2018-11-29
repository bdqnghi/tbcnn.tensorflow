package com.codecool.bfsexample;

import com.codecool.bfsexample.model.UserNode;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.EntityTransaction;
import javax.persistence.Persistence;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class BFSExample {

    public static List<UserNode> populateDB(EntityManager em) {

        RandomDataGenerator generator = new RandomDataGenerator();
        List<UserNode> users = generator.generate();

        EntityTransaction transaction = em.getTransaction();
        transaction.begin();
        for (UserNode user : users) {
            em.persist(user);
        }
        transaction.commit();

        GraphPlotter.plot(users);
        
        System.out.println("Done!");

        return users;
    }

    public static void main(String[] args) {
        EntityManagerFactory emf = Persistence.createEntityManagerFactory("bfsExampleUnit");
        EntityManager em = emf.createEntityManager();

        em.clear();

        List<UserNode> happyTreeFriends = populateDB(em);

        BreadthFirstSearch breadthFirstSearch = new BreadthFirstSearch();

        breadthFirstSearch.breadthFirstSearch(happyTreeFriends.get(2), happyTreeFriends.get(8));
        System.out.println(breadthFirstSearch.getDistance());

        breadthFirstSearch.breadthFirstSearch(happyTreeFriends.get(8), happyTreeFriends.get(2));
        System.out.println(breadthFirstSearch.getDistance());

        Set<UserNode> friendsOfNode = breadthFirstSearch.friendsOfFriends(happyTreeFriends.get(3), 2);
        Map<UserNode, Integer> userDistance = breadthFirstSearch.getUserDistance();
        System.out.println("FRIENDS OF "+happyTreeFriends.get(3).getId()+": " + happyTreeFriends.get(3).getFirstName() +
                            " " + happyTreeFriends.get(3).getLastName());
        for(UserNode friend: friendsOfNode) {
            System.out.println("Connection line " + userDistance.get(friend) + "\n" +
                                "Friend "+friend.getId()+" : " + friend.getFirstName() + " " + friend.getLastName());
        }

        List<String> shortestPath =
                breadthFirstSearch.findShortest("Christopher Myles", "Christopher Hillary", happyTreeFriends);
        System.out.println(shortestPath);
    }
}
