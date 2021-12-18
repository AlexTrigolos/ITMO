import com.javatunes.util.ItemDAO;
import com.javatunes.util.MusicItem;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Collection;

public class JDBCOracle {
    public static void main(String[] args) throws ClassNotFoundException, SQLException {
        MusicItem musItem1;
        Connection connection = null;
        Class.forName("org.apache.derby.jdbc.ClientDriver");
        connection = DriverManager.getConnection("jdbc:derby://localhost:1527/JavaTunesDB", "GUEST", "password");
        ItemDAO itemDAO = new ItemDAO(connection);
        musItem1 = itemDAO.searchById(1L);
        MusicItem musItem100;
        musItem100 = itemDAO.searchById(100L);
        if (musItem1 != null) {
            System.out.println(musItem1);
        } else {
            System.out.println("Haven't Id");
        }
        if (musItem100 != null) {
            System.out.println(musItem100);
        } else {
            System.out.println("Haven't Id");
        }
        System.out.println("of:");
        Collection<MusicItem> musItemsOf = itemDAO.searchByKeyword("of");
        if (musItemsOf != null) {
            for (MusicItem item : musItemsOf) {
                System.out.println(item.toString());
            }
        }
        System.out.println("Gay:");
        Collection<MusicItem> musicItemsGay = itemDAO.searchByKeyword("Gay");
        if (musicItemsGay != null) {
            for (MusicItem item : musicItemsGay) {
                System.out.println(item.toString());
            }
        }
    }
}
