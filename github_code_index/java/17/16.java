package com.company;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.*;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.awt.*;
import java.io.File;
import java.util.Scanner;


import static com.company.Node.IConstants.RED;

public class Main extends Application{
    private File file = new File("3_insert.txt");
    @Override
    public void start(Stage primaryStage){
        //建两颗树并初始化
        Red_Black_Tree red_black_tree = new Red_Black_Tree();
        red_black_tree.initiate();
        B_Add_Tree b_add_tree = new B_Add_Tree(4);
        b_add_tree.initiate(b_add_tree);

        //Ui
        BorderPane pane = new BorderPane();
        HBox hBox = new HBox();
        hBox.setPadding(new Insets(20,20,20,20));
        VBox vBoxRight = new VBox();
        vBoxRight.setMinWidth(400);
        VBox vBoxLeft = new VBox();
        vBoxLeft.setMinWidth(400);

        Label mana = new Label("MANAGEMENT");
        FlowPane pane1 = new FlowPane(20,20);
        pane1.setPadding(new Insets(30,30,30,30));
        pane1.setStyle("-fx-border: 5px solid; -fx-border-color: lightBlue; -fx-background-radius: 3.0;"
                + "-fx-border-radius: 3.0");
        pane1.setAlignment(Pos.CENTER);
        TextField textField1 = new TextField();
        textField1.setMinWidth(300);
        FileChooser fileChooser = new FileChooser();
        Button buttonBrowser = new Button("Browser");
        Button buttonSubmit = new Button("InsertFile");
        Button buttonDelete = new Button("DeleteFile");
        pane1.getChildren().addAll(textField1,buttonBrowser,buttonSubmit,buttonDelete);

        FlowPane pane2 = new FlowPane(5,5);
        pane2.setPadding(new Insets(30,30,30,30));
        pane2.setStyle("-fx-border: 5px solid; -fx-border-color: lightBlue; -fx-background-radius: 3.0;"
                + "-fx-border-radius: 3.0");
        pane2.setAlignment(Pos.CENTER);
        Label english = new Label("English");
        TextField engText = new TextField();
        engText.setMaxWidth(100);
        Label chinese = new Label("Chinese");
        TextField chiText = new TextField();
        chiText.setMaxWidth(100);
        Button btAdd = new Button("Add");
        Button btDel = new Button("Delete");
        pane2.getChildren().setAll(english,engText,chinese,chiText,btAdd,btDel);

        vBoxLeft.getChildren().addAll(mana,pane1,pane2);
        vBoxLeft.setSpacing(10);
        vBoxLeft.setFillWidth(true);

        FlowPane pane3 = new FlowPane(5,5);
        pane3.setPadding(new Insets(25,25,25,25));
        pane3.setStyle("-fx-border: 5px solid; -fx-border-color: lightBlue; -fx-background-radius: 3.0;"
                + "-fx-border-radius: 3.0");
        pane3.setAlignment(Pos.CENTER);
        ToggleGroup toggleGroup = new ToggleGroup();
        RadioButton radioButton1 = new RadioButton("red-black-tree");
        radioButton1.setSelected(true);
        RadioButton radioButton2 = new RadioButton("B+ tree");
        radioButton1.setToggleGroup(toggleGroup);
        radioButton2.setToggleGroup(toggleGroup);
        pane3.getChildren().addAll(radioButton1,radioButton2);

        FlowPane pane4 = new FlowPane(5,5);
        pane4.setPadding(new Insets(25,25,25,25));
        pane4.setStyle("-fx-border: 5px solid; -fx-border-color: lightBlue; -fx-background-radius: 3.0;"
                + "-fx-border-radius: 3.0");
        pane4.setAlignment(Pos.CENTER);
        TextField textField_Tran = new TextField();
        Button button_Tran = new Button("Translate");
        pane4.getChildren().addAll(textField_Tran,button_Tran);

        FlowPane pane5 = new FlowPane(15,15);
        pane5.setMaxWidth(300);
        pane5.setPadding(new Insets(10,-68,10,-70));
        pane5.setStyle("-fx-border: 5px solid; -fx-border-color: lightBlue; -fx-background-radius: 3.0;"
                + "-fx-border-radius: 3.0");
        pane5.setAlignment(Pos.CENTER);
        Label search = new Label("Search from");
        TextField search_Text = new TextField();
        search_Text.setMaxWidth(80);
        Label to = new Label("to");
        TextField to_Text = new TextField();
        to_Text.setMaxWidth(80);
        Button sub = new Button("Submit");

        TextArea textArea = new TextArea();
        textArea.setMaxHeight(8);
        textArea.setMaxWidth(250);
        pane5.getChildren().addAll(search,search_Text,to,to_Text,sub,textArea);

        vBoxRight.getChildren().addAll(pane3,pane4,pane5);
        vBoxRight.setSpacing(10);
        vBoxRight.setPadding(new Insets(10,10,10,10));
        vBoxRight.setStyle("-fx-border: 5px solid; -fx-border-color: lightBlue; -fx-background-radius: 3.0;"
                + "-fx-border-radius: 3.0");

        hBox.getChildren().addAll(vBoxLeft,vBoxRight);
        hBox.setSpacing(20);
        pane.getChildren().add(hBox);

        button_Tran.setOnMouseClicked(new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent event) {
                String engWord = textField_Tran.getText();
                if(radioButton1.isSelected()) {
                    try {
                        Node node = red_black_tree.search(engWord,false);
                        textArea.setText(node.getValue());
                    }catch (Exception e){
                        textArea.setText("The word you need translate is not exist!");
                    }
                }
                else{
                    try {
                        String explain = (String)b_add_tree.search(engWord);
                        if(explain != null) {
                            textArea.setText(explain);
                        }
                        else {
                            textArea.setText("The word you need translate is not exist!");
                        }
                    }
                    catch (Exception e){
                        textArea.setText("The word you need translate is not exist!");
                    }
                }
            }
        });
        sub.setOnMouseClicked(new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent event) {
                String from = search_Text.getText();
                String to = to_Text.getText();
                if(radioButton1.isSelected()) {
                    if (from.toLowerCase().compareTo(to.toLowerCase()) <= 0 && red_black_tree.search(from, false) != null && red_black_tree.search(to, false) != null) {
                        String begin = from + " " + red_black_tree.search(from, false).getValue() + "\n";
                        Node success = red_black_tree.successor(red_black_tree.search(from, false));
                        while (success != null && success.getKey().toLowerCase().compareTo(to.toLowerCase()) <= 0) {
                            begin = begin + success.getKey() + " " + success.getValue() + "\n";
                            from = success.getKey();
                            success = red_black_tree.successor(red_black_tree.search(from, false));
                        }
                        textArea.setText(begin);
                    }
                    else {
                        textArea.setText("Your search range is illegal!");
                    }
                }
                else {
                    if (from.compareTo(to) <= 0 && b_add_tree.search(from) != null && b_add_tree.search(to) != null){
                        String begin =from + " " + (String)b_add_tree.search(from) + "\n";
                        Node success = red_black_tree.successor(red_black_tree.search(from, false));
                        while (success != null && success.getKey().compareTo(to.toLowerCase()) <= 0){
                            begin += success.getKey() + " " + b_add_tree.search(success.getKey()) + "\n";
                            from = success.getKey();
                            success = red_black_tree.successor(red_black_tree.search(from, false));
                        }
                        textArea.setText(begin);
                    }
                    else{
                        textArea.setText("Your search range is illegal!");
                    }

                }
            }
        });
        btAdd.setOnMouseClicked(new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent event) {
                String eng = engText.getText();
                String chi = chiText.getText();
                if(radioButton1.isSelected()){
                    red_black_tree.insert(new Node(eng,RED,chi));
                    textArea.setText("Insert or update successfully by red-black-tree!");
                }
                else {
                    b_add_tree.insertOrUpdate(eng,chi);
                    textArea.setText("Insert or update successfully by B+ tree!");
                }
            }
        });
        btDel.setOnMouseClicked(new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent event) {
                String eng = engText.getText();
                String chi = chiText.getText();
                if(radioButton1.isSelected()){
                    red_black_tree.delete(red_black_tree.search(eng,false));
                    textArea.setText("Delete successfully by red-black-tree if the key is exist!");
                }
                else {
                    b_add_tree.delete(eng);
                    textArea.setText("Delete successfully by B+ tree if the key is exist!");
                }
            }
        });
        buttonSubmit.setOnMouseClicked(new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent event) {
                if(radioButton1.isSelected()){
                    red_black_tree.insertFile();
                    textArea.setText("Successful insert file");
                }
                else{
                    b_add_tree.insertFile();
                    textArea.setText("Successful insert file");
                }
            }
        });
        buttonDelete.setOnMouseClicked(new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent event) {
                if(radioButton1.isSelected()){
                    red_black_tree.deleteFile();
                    textArea.setText("Successful delete file");
                }
                else{
                    b_add_tree.deleteFile();
                    textArea.setText("Successful delete file");
                }
            }
        });
        buttonBrowser.setOnMouseClicked(new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent event) {
                if(file.toString().indexOf("3_insert.txt") != -1
                        || file.toString().indexOf("2_delete.txt") != -1){
                    textArea.setText("I am ready!");
                    file = new File("");
                }
                else {
                    textArea.setText("Not ready! The file is not legal! Use default file!");
                    try {
                        file = fileChooser.showOpenDialog(primaryStage);
                    } catch (Exception e) {

                    }
                }

            }
        });

        Scene scene = new Scene(pane,900,320);
        primaryStage.setScene(scene);
        primaryStage.setTitle("English_Chinese Dictionary");
        primaryStage.show();
    }
    public static void main(String[] args) {
        launch(args);
	// write your code here
        Red_Black_Tree tree = new Red_Black_Tree();
        System .out.println("The first you test is red-black-tree:\n");

        tree.initiate();
        System.out.println("First, insert into trees the data in the file 1_initial.txt as follows, " +
                "\nShow pre_order below:");
        tree.preorder_tree_walk(tree.getRoot(),0,0);


        System.out.println("\nEnter the word you want to delete" +
                "\n（input \"file_delete\" means delete the data in the file 2_delete.txt）:");
        Scanner input1 = new Scanner(System.in);
        String word_delete = input1.nextLine();
        if(word_delete.equals("file_delete")){
            long b = System.nanoTime();
            tree.deleteFile();
            long e = System.nanoTime();
            System.out.println("delete file use "+ (e-b) + "ns");
        }
        else {
            Node del = tree.search(word_delete,false);
            if(del != null) {
                tree.delete(del);
            }
            else {
                System.out.println("There isn't the word to delete! fuck!");
            }
        }


        System.out.println("Enter the word you want to insert:" +
                "\n(\"word  meaning\" or \"file_insert\"):");
        String word_insert = input1.next();
        if(word_insert.equals("file_insert")){
            long b = System.nanoTime();
            tree.insertFile();
            long e = System.nanoTime();
            System.out.println("insert use "+ (e-b) + "ns");
        }
        else {
            String now_Explain = input1.next();
            tree.insert(new Node(word_insert,RED,now_Explain));
        }

        System.out.println("Enter the word you want to query:");
        String word_query = input1.next();
        tree.search(word_query,true);

        System.out.println("Enter the range you want to query:");
        String gabbage = input1.next();
        String begin = input1.next();
        gabbage = input1.next();
        String end = input1.next();
        if(end.compareTo(begin) != 0) {
            tree.printOnRoad(begin, end);
        }


        System.out.println("Next, we test B+ tree:\n\nEnter a number as order:");
        B_Add_Tree.main(null);
    }
}
