package lhc.domain;

import java.util.ArrayList;
import java.util.List;

import javax.persistence.MappedSuperclass;
import javax.persistence.Transient;

import com.google.common.base.Joiner;

@MappedSuperclass
public abstract class DsxJyYz extends BaseYz {
	private Integer specialNum;
	private String c1Nums;
	private String c2Nums;
	private String c3Nums;
	private String c4Nums;
	private String c5Nums;
	private String c6Nums;
	private String c7Nums;
	private String c8Nums;
	private String c9Nums;
	private String c10Nums;
	private String c11Nums;
	private String c1NumsReverse;
	private String c2NumsReverse;
	private String c3NumsReverse;
	private String c4NumsReverse;
	private String c5NumsReverse;
	private String c6NumsReverse;
	private String c7NumsReverse;
	private String c8NumsReverse;
	private String c9NumsReverse;
	private String c10NumsReverse;
	private String c11NumsReverse;
	private String c1NumsXc;
	private String c2NumsXc;
	private String c3NumsXc;
	private String c4NumsXc;
	private String c5NumsXc;
	private String c6NumsXc;
	private String c7NumsXc;
	private String c8NumsXc;
	private String c9NumsXc;
	private String c10NumsXc;
	private String c11NumsXc;

	@Transient
	private String c1n;
	@Transient
	private String c2n;
	@Transient
	private String c3n;
	@Transient
	private String c4n;
	@Transient
	private String c5n;
	@Transient
	private String c6n;
	@Transient
	private String c7n;
	@Transient
	private String c8n;
	@Transient
	private String c9n;
	@Transient
	private String c10n;
	@Transient
	private String c11n;

	@Transient
	private List<Integer> c1 = new ArrayList<Integer>();
	@Transient
	private List<Integer> c2 = new ArrayList<Integer>();
	@Transient
	private List<Integer> c3 = new ArrayList<Integer>();
	@Transient
	private List<Integer> c4 = new ArrayList<Integer>();
	@Transient
	private List<Integer> c5 = new ArrayList<Integer>();
	@Transient
	private List<Integer> c6 = new ArrayList<Integer>();
	@Transient
	private List<Integer> c7 = new ArrayList<Integer>();
	@Transient
	private List<Integer> c8 = new ArrayList<Integer>();
	@Transient
	private List<Integer> c9 = new ArrayList<Integer>();
	@Transient
	private List<Integer> c10 = new ArrayList<Integer>();
	@Transient
	private List<Integer> c11 = new ArrayList<Integer>();
	
	public void reset() {
		specialNum = null;
		c1Nums = null;
		c2Nums = null;
		c3Nums = null;
		c4Nums = null;
		c5Nums = null;
		c6Nums = null;
		c7Nums = null;
		c8Nums = null;
		c9Nums = null;
		c10Nums = null;
		c11Nums = null;
		c1NumsReverse = null;
		c2NumsReverse = null;
		c3NumsReverse = null;
		c4NumsReverse = null;
		c5NumsReverse = null;
		c6NumsReverse = null;
		c7NumsReverse = null;
		c8NumsReverse = null;
		c9NumsReverse = null;
		c10NumsReverse = null;
		c11NumsReverse = null;
		c1NumsXc = null;
		c2NumsXc = null;
		c3NumsXc = null;
		c4NumsXc = null;
		c5NumsXc = null;
		c6NumsXc = null;
		c7NumsXc = null;
		c8NumsXc = null;
		c9NumsXc = null;
		c10NumsXc = null;
		c11NumsXc = null;
	}

	public void clearAll() {
		c1.clear();
		c2.clear();
		c3.clear();
		c4.clear();
		c5.clear();
		c6.clear();
		c7.clear();
		c8.clear();
		c9.clear();
		c10.clear();
		c11.clear();
	}

	private String getJoinString(List<Integer> c) {
		String str = Joiner.on(",").join(c);
		return !str.isEmpty() ? str : null;
	}

	public void assemble(boolean qc, boolean reverse) {
		if (!qc) {
			c1NumsXc = getJoinString(c1);
			c2NumsXc = getJoinString(c2);
			c3NumsXc = getJoinString(c3);
			c4NumsXc = getJoinString(c4);
			c5NumsXc = getJoinString(c5);
			c6NumsXc = getJoinString(c6);
			c7NumsXc = getJoinString(c7);
			c8NumsXc = getJoinString(c8);
			c9NumsXc = getJoinString(c9);
			c10NumsXc = getJoinString(c10);
			c11NumsXc = getJoinString(c11);
		} else {
			if (reverse) {
				c1NumsReverse = getJoinString(c1);
				c2NumsReverse = getJoinString(c2);
				c3NumsReverse = getJoinString(c3);
				c4NumsReverse = getJoinString(c4);
				c5NumsReverse = getJoinString(c5);
				c6NumsReverse = getJoinString(c6);
				c7NumsReverse = getJoinString(c7);
				c8NumsReverse = getJoinString(c8);
				c9NumsReverse = getJoinString(c9);
				c10NumsReverse = getJoinString(c10);
				c11NumsReverse = getJoinString(c11);
			} else {
				c1Nums = getJoinString(c1);
				c2Nums = getJoinString(c2);
				c3Nums = getJoinString(c3);
				c4Nums = getJoinString(c4);
				c5Nums = getJoinString(c5);
				c6Nums = getJoinString(c6);
				c7Nums = getJoinString(c7);
				c8Nums = getJoinString(c8);
				c9Nums = getJoinString(c9);
				c10Nums = getJoinString(c10);
				c11Nums = getJoinString(c11);
			}
		}
	}

	public String getC11Nums() {
		return c11Nums;
	}

	public void setC11Nums(String c11Nums) {
		this.c11Nums = c11Nums;
	}

	public String getC11NumsReverse() {
		return c11NumsReverse;
	}

	public void setC11NumsReverse(String c11NumsReverse) {
		this.c11NumsReverse = c11NumsReverse;
	}

	public String getC11NumsXc() {
		return c11NumsXc;
	}

	public void setC11NumsXc(String c11NumsXc) {
		this.c11NumsXc = c11NumsXc;
	}

	public List<Integer> getC11() {
		return c11;
	}

	public void setC11(List<Integer> c11) {
		this.c11 = c11;
	}

	public String getC11n() {
		return c11n;
	}

	public void setC11n(String c11n) {
		this.c11n = c11n;
	}

	public Integer getSpecialNum() {
		return specialNum;
	}

	public void setSpecialNum(Integer specialNum) {
		this.specialNum = specialNum;
	}

	public String getC1n() {
		return c1n;
	}

	public void setC1n(String c1n) {
		this.c1n = c1n;
	}

	public String getC2n() {
		return c2n;
	}

	public void setC2n(String c2n) {
		this.c2n = c2n;
	}

	public String getC3n() {
		return c3n;
	}

	public void setC3n(String c3n) {
		this.c3n = c3n;
	}

	public String getC4n() {
		return c4n;
	}

	public void setC4n(String c4n) {
		this.c4n = c4n;
	}

	public String getC5n() {
		return c5n;
	}

	public void setC5n(String c5n) {
		this.c5n = c5n;
	}

	public String getC6n() {
		return c6n;
	}

	public void setC6n(String c6n) {
		this.c6n = c6n;
	}

	public String getC7n() {
		return c7n;
	}

	public void setC7n(String c7n) {
		this.c7n = c7n;
	}

	public String getC8n() {
		return c8n;
	}

	public void setC8n(String c8n) {
		this.c8n = c8n;
	}

	public String getC9n() {
		return c9n;
	}

	public void setC9n(String c9n) {
		this.c9n = c9n;
	}

	public String getC10n() {
		return c10n;
	}

	public void setC10n(String c10n) {
		this.c10n = c10n;
	}

	public String getC1NumsReverse() {
		return c1NumsReverse;
	}

	public void setC1NumsReverse(String c1NumsReverse) {
		this.c1NumsReverse = c1NumsReverse;
	}

	public String getC2NumsReverse() {
		return c2NumsReverse;
	}

	public void setC2NumsReverse(String c2NumsReverse) {
		this.c2NumsReverse = c2NumsReverse;
	}

	public String getC3NumsReverse() {
		return c3NumsReverse;
	}

	public void setC3NumsReverse(String c3NumsReverse) {
		this.c3NumsReverse = c3NumsReverse;
	}

	public String getC4NumsReverse() {
		return c4NumsReverse;
	}

	public void setC4NumsReverse(String c4NumsReverse) {
		this.c4NumsReverse = c4NumsReverse;
	}

	public String getC5NumsReverse() {
		return c5NumsReverse;
	}

	public void setC5NumsReverse(String c5NumsReverse) {
		this.c5NumsReverse = c5NumsReverse;
	}

	public String getC6NumsReverse() {
		return c6NumsReverse;
	}

	public void setC6NumsReverse(String c6NumsReverse) {
		this.c6NumsReverse = c6NumsReverse;
	}

	public String getC7NumsReverse() {
		return c7NumsReverse;
	}

	public void setC7NumsReverse(String c7NumsReverse) {
		this.c7NumsReverse = c7NumsReverse;
	}

	public String getC8NumsReverse() {
		return c8NumsReverse;
	}

	public void setC8NumsReverse(String c8NumsReverse) {
		this.c8NumsReverse = c8NumsReverse;
	}

	public String getC9NumsReverse() {
		return c9NumsReverse;
	}

	public void setC9NumsReverse(String c9NumsReverse) {
		this.c9NumsReverse = c9NumsReverse;
	}

	public String getC10NumsReverse() {
		return c10NumsReverse;
	}

	public void setC10NumsReverse(String c10NumsReverse) {
		this.c10NumsReverse = c10NumsReverse;
	}

	public String getC1NumsXc() {
		return c1NumsXc;
	}

	public void setC1NumsXc(String c1NumsXc) {
		this.c1NumsXc = c1NumsXc;
	}

	public String getC2NumsXc() {
		return c2NumsXc;
	}

	public void setC2NumsXc(String c2NumsXc) {
		this.c2NumsXc = c2NumsXc;
	}

	public String getC3NumsXc() {
		return c3NumsXc;
	}

	public void setC3NumsXc(String c3NumsXc) {
		this.c3NumsXc = c3NumsXc;
	}

	public String getC4NumsXc() {
		return c4NumsXc;
	}

	public void setC4NumsXc(String c4NumsXc) {
		this.c4NumsXc = c4NumsXc;
	}

	public String getC5NumsXc() {
		return c5NumsXc;
	}

	public void setC5NumsXc(String c5NumsXc) {
		this.c5NumsXc = c5NumsXc;
	}

	public String getC6NumsXc() {
		return c6NumsXc;
	}

	public void setC6NumsXc(String c6NumsXc) {
		this.c6NumsXc = c6NumsXc;
	}

	public String getC7NumsXc() {
		return c7NumsXc;
	}

	public void setC7NumsXc(String c7NumsXc) {
		this.c7NumsXc = c7NumsXc;
	}

	public String getC8NumsXc() {
		return c8NumsXc;
	}

	public void setC8NumsXc(String c8NumsXc) {
		this.c8NumsXc = c8NumsXc;
	}

	public String getC9NumsXc() {
		return c9NumsXc;
	}

	public void setC9NumsXc(String c9NumsXc) {
		this.c9NumsXc = c9NumsXc;
	}

	public String getC10NumsXc() {
		return c10NumsXc;
	}

	public void setC10NumsXc(String c10NumsXc) {
		this.c10NumsXc = c10NumsXc;
	}

	public List<Integer> getC1() {
		return c1;
	}

	public void setC1(List<Integer> c1) {
		this.c1 = c1;
	}

	public List<Integer> getC2() {
		return c2;
	}

	public void setC2(List<Integer> c2) {
		this.c2 = c2;
	}

	public List<Integer> getC3() {
		return c3;
	}

	public void setC3(List<Integer> c3) {
		this.c3 = c3;
	}

	public List<Integer> getC4() {
		return c4;
	}

	public void setC4(List<Integer> c4) {
		this.c4 = c4;
	}

	public List<Integer> getC5() {
		return c5;
	}

	public void setC5(List<Integer> c5) {
		this.c5 = c5;
	}

	public List<Integer> getC6() {
		return c6;
	}

	public void setC6(List<Integer> c6) {
		this.c6 = c6;
	}

	public List<Integer> getC7() {
		return c7;
	}

	public void setC7(List<Integer> c7) {
		this.c7 = c7;
	}

	public List<Integer> getC8() {
		return c8;
	}

	public void setC8(List<Integer> c8) {
		this.c8 = c8;
	}

	public List<Integer> getC9() {
		return c9;
	}

	public void setC9(List<Integer> c9) {
		this.c9 = c9;
	}

	public List<Integer> getC10() {
		return c10;
	}

	public void setC10(List<Integer> c10) {
		this.c10 = c10;
	}

	public String getC1Nums() {
		return c1Nums;
	}

	public void setC1Nums(String c1Nums) {
		this.c1Nums = c1Nums;
	}

	public String getC2Nums() {
		return c2Nums;
	}

	public void setC2Nums(String c2Nums) {
		this.c2Nums = c2Nums;
	}

	public String getC3Nums() {
		return c3Nums;
	}

	public void setC3Nums(String c3Nums) {
		this.c3Nums = c3Nums;
	}

	public String getC4Nums() {
		return c4Nums;
	}

	public void setC4Nums(String c4Nums) {
		this.c4Nums = c4Nums;
	}

	public String getC5Nums() {
		return c5Nums;
	}

	public void setC5Nums(String c5Nums) {
		this.c5Nums = c5Nums;
	}

	public String getC6Nums() {
		return c6Nums;
	}

	public void setC6Nums(String c6Nums) {
		this.c6Nums = c6Nums;
	}

	public String getC7Nums() {
		return c7Nums;
	}

	public void setC7Nums(String c7Nums) {
		this.c7Nums = c7Nums;
	}

	public String getC8Nums() {
		return c8Nums;
	}

	public void setC8Nums(String c8Nums) {
		this.c8Nums = c8Nums;
	}

	public String getC9Nums() {
		return c9Nums;
	}

	public void setC9Nums(String c9Nums) {
		this.c9Nums = c9Nums;
	}

	public String getC10Nums() {
		return c10Nums;
	}

	public void setC10Nums(String c10Nums) {
		this.c10Nums = c10Nums;
	}
}
