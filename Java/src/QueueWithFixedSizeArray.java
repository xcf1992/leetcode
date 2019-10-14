import java.util.ArrayList;
import java.util.List;

public class QueueWithFixedSizeArray {
    private int count;
    private int headP;
    private int tailP;
    private int limit;

    List<Object> head;
    List<Object> tail;

    public QueueWithFixedSizeArray(int sizeLimit) {
        this.count = 0;
        this.headP = 0;
        this.tailP = 0;
        this.limit = sizeLimit;

        this.head = new ArrayList<Object>();
        this.tail = this.head;
    }

    public void offer(int num) {
        if (this.tailP == this.limit - 1) {
            List<Object> next = new ArrayList<Object>();
            this.tail.add(next);
            this.tail = next;
            this.tailP = 0;
        }
        this.tail.add(num);
        this.tailP += 1;
        this.count += 1;
    }

    public Integer poll() {
        if (count == 0) {
            return null;
        }

        int result = (Integer) head.get(headP);
        headP += 1;
        count -= 1;
        if (headP == limit - 1) {
            head = (List<Object>) head.get(headP);
            headP = 0;
        }
        return result;
    }

    public int size() {
        return this.count;
    }
}
