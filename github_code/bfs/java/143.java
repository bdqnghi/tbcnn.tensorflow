import java.awt.Point;
import java.util.LinkedList;
import java.util.Queue;

public class Pathfinder {
	
	public static class PointBFS {
		int x;
		int y;
		PointBFS parent;
		
		PointBFS(int _x, int _y, PointBFS _parent){
			x = _x;
			y = _y;
			parent = _parent;
		}
		
		public PointBFS getParent(){
			return parent;
		}
		
		public Point getPos(){
			return (new Point(x,y));
		}
	}
	
	@SuppressWarnings("unused")
	private boolean isParentOf(PointBFS p, int x, int y){
		while(p.getParent() != null){
			if(p.x == x && p.y == y) return true;
			p = p.getParent();
		}
		return false;
	}
	
	private Queue<PointBFS> q;
	public PointBFS pathfindBFS(Point start, Point end, int[][] temp, boolean diagonals){
		q = new LinkedList<PointBFS>();
		q.add(new PointBFS(start.x,start.y,null));
		
		while (!q.isEmpty()) {
			PointBFS p = q.remove();
			if (p.x == end.x && p.y == end.y) {
				return p;
			}
			if(!isOpen(p,q,p.x,p.y,temp)){
				break;
			}
			
			// up
			if(isOpen(p,q, p.x,p.y-1,temp)){
				temp[p.y][p.x] = -1;
				PointBFS next = new PointBFS(p.x,p.y-1,p);
				q.add(next);
			}
			// right
			if(isOpen(p,q, p.x+1,p.y,temp)){
				temp[p.y][p.x] = -1;
				PointBFS next = new PointBFS(p.x+1,p.y,p);
				q.add(next);
			}
			// down
			if(isOpen(p,q, p.x,p.y+1,temp)){
				temp[p.y][p.x] = -1;
				PointBFS next = new PointBFS(p.x,p.y+1,p);
				q.add(next);
			}
			// left
			if(isOpen(p,q, p.x-1,p.y,temp)){
				temp[p.y][p.x] = -1;
				PointBFS next = new PointBFS(p.x-1,p.y,p);
				q.add(next);
			}
			
			if(diagonals){
				if(diagonalCheck(4,p,q,temp)){
					temp[p.y][p.x] = -1;
					PointBFS next = new PointBFS(p.x+1,p.y-1,p);
					q.add(next);
				}
				
				if(diagonalCheck(5,p,q,temp)){
					temp[p.y][p.x] = -1;
					PointBFS next = new PointBFS(p.x+1,p.y+1,p);
					q.add(next);
				}
				
				if(diagonalCheck(6,p,q,temp)){
					temp[p.y][p.x] = -1;
					PointBFS next = new PointBFS(p.x-1,p.y+1,p);
					q.add(next);
				}
				
				if(diagonalCheck(7,p,q,temp)){
					temp[p.y][p.x] = -1;
					PointBFS next = new PointBFS(p.x-1,p.y-1,p);
					q.add(next);
				}
				
			}
		}
		
		return null;
	}
	
	private boolean isOpen(PointBFS p, Queue<PointBFS> q,int _x, int _y, int[][] _map){
		if (q!=null) {
			// if(isParentOf(p,x,y)) return false;
			for (PointBFS i : q) {
				if (i.x == _x && i.y == _y)
					return false;
			}
		}
		if(_x<0 || _y<0 || _y>=_map.length || _x>=_map[_y].length) return false;
		if(_map[_y][_x] != 1 && _map[_y][_x] != 6) return true;
		return false;
	}
	
	private boolean diagonalCheck(int dir, PointBFS p, Queue<PointBFS> q, int[][] temp){
		int x = p.x;
		int y = p.y;
		int blocks = 0;
		if((dir == 4 || dir == 5)&& !isOpen(p,null,x+1, y,temp)) blocks++;
		if((dir == 5 || dir == 6)&& !isOpen(p,null,x, y+1,temp)) blocks++;
		if((dir == 6 || dir == 7)&& !isOpen(p,null,x-1, y,temp)) blocks++;
		if((dir == 7 || dir == 4)&& !isOpen(p,null,x, y-1 ,temp)) blocks++;
		
		if(blocks>=2) return false;
		
		if(dir == 4 && !isOpen(p,q,x+1,y-1,temp)) return false;
		if(dir == 5 && !isOpen(p,q,x+1,y+1,temp)) return false;
		if(dir == 6 && !isOpen(p,q,x-1,y+1,temp)) return false;
		if(dir == 7 && !isOpen(p,q,x-1,y-1,temp)) return false;
		
		return true;
	}

}
