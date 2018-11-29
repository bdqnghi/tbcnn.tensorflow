package com.github.Higman.hanoi;

import com.github.Higman.DrawableHanoiAlgorithm;
import kotlin.jvm.functions.Function0;
import org.jetbrains.annotations.NotNull;
import sun.reflect.generics.reflectiveObjects.NotImplementedException;

import java.util.*;
import java.util.concurrent.CopyOnWriteArrayList;

public class HanoiWalshAlgorithm extends HanoiAlgorithmComp implements DrawableHanoiAlgorithm {
    private Optional<HanoiWalshParameter> hanoiWalshParameter = Optional.empty();

    public HanoiWalshAlgorithm(Hanoi hanoi) {
        super(hanoi);
    }

    /**
     * ウォルシュアルゴリズムの実行
     */
    @Override
    public void execHanoi() {
        System.out.println("== Start");
        System.out.println(hanoi);
        initialize();
        while ( true ) {
            System.out.println("========");
            if ( !firstStepWithOutput() ) { break; }   // 第1移動
            if ( hanoi.isFinished() ) { break; }  // 終了判定
            if ( !secondStepWithOutput() ) { break; }  // 第2移動
            System.out.println(hanoi);
        }
        hanoiWalshParameter = Optional.empty();
        System.out.println("== End");
        System.out.println(hanoi);
    }

    public List<Hanoi> getProcessAsync() {
        List<Hanoi> hanoiList = new CopyOnWriteArrayList<>();

        throw new NotImplementedException();

//        return hanoiList;
    }

    /**
     * ウォルシュアルゴリズムに必要なパラメタの更新
     */
    private void updateStatusHanoiWalsh() {
        hanoiWalshParameter.ifPresent(param -> {
            param.towerIDHavingSmallestDisk = getTowerIDHavingSmallestDisk();
            param.towerIDHavingEvenDisk =getTowerIDHavingEvenDisk(param.towerIDHavingSmallestDisk);
            param.towerIDOfSecondTower = getTowerIDHavingSmallestDisk(param.towerIDHavingSmallestDisk);
            param.towerIDOfOtherTower = getTowerIDOfOtherTower(param.towerIDHavingSmallestDisk, param.towerIDOfSecondTower);
        });
    }

    /**
     * 最小の円盤移動の処理(標準出力付き)
     *
     * @return 処理の成功/失敗
     */
    protected boolean firstStepWithOutput() {
        Optional<MoveInformation> param = firstStep();
        if ( !param.isPresent() ) { return false; }                              // 例外判定
        param.ifPresent(info -> System.out.println("  = Move1: " + info.movingSource + " ==> " + info.destination));
        return true;
    }

    /**
     * 最小の円盤移動の処理
     *
     * @return 処理の成功/失敗
     */
    protected Optional<MoveInformation> firstStep() {
        if ( !hanoiWalshParameter.isPresent() ) { return Optional.empty(); }           // 例外判定
        HanoiWalshParameter param = hanoiWalshParameter.get();
        MoveInformation mi = new MoveInformation(param.towerIDHavingSmallestDisk, param.towerIDHavingEvenDisk);
        hanoi.move(param.towerIDHavingSmallestDisk, param.towerIDHavingEvenDisk);                 // 円盤の移動
        updateStatusHanoiWalsh();
        return Optional.of(mi);
    }

    /**
     * 第2円盤の移動処理(標準出力付き)
     *
     * @return 処理の成功/失敗
     */
    protected boolean secondStepWithOutput() {
        Optional<MoveInformation> param = secondStep();
        if ( !param.isPresent() ) { return false; }                              // 例外判定
        param.ifPresent(info -> System.out.println("  = Move1: " + info.movingSource + " ==> " + info.destination));
        return true;
    }

    /**
     * 第2円盤の移動処理
     *
     * @return 処理の成功/失敗
     */
    protected Optional<MoveInformation> secondStep() {
        if ( !hanoiWalshParameter.isPresent() ) { return Optional.empty(); }           // 例外判定
        HanoiWalshParameter param = hanoiWalshParameter.get();
        MoveInformation mi = new MoveInformation(param.towerIDOfSecondTower, param.towerIDOfOtherTower);
        hanoi.move(param.towerIDOfSecondTower, param.towerIDOfOtherTower);                 // 円盤の移動
        updateStatusHanoiWalsh();
        return Optional.of(mi);
    }

    @Override
    public void initialize() {
        hanoiWalshParameter = Optional.of(new HanoiWalshParameter());
        updateStatusHanoiWalsh();
    }


    private Hanoi.TowerID getTowerIDHavingEvenDisk(Hanoi.TowerID excludeTowerID) {
        Hanoi.TowerInformation towerInfoHavingEvenDisk = null;
        Hanoi.TowerID[] searchIDs = Arrays.stream(Hanoi.TowerID.values()).filter(id -> id != excludeTowerID).toArray(Hanoi.TowerID[]::new);
        for ( Hanoi.TowerID id : searchIDs ) {
            Hanoi.TowerInformation tmpInfo = hanoi.getInfo(id);
            if ( tmpInfo.topDisk.label % 2 == 0 ) { towerInfoHavingEvenDisk = tmpInfo; }
        }
        return towerInfoHavingEvenDisk.towerID;
    }

    @NotNull
    @Override
    public List<Function0<Optional<MoveInformation>>> getSortOperations() {
        return new ArrayList<Function0<Optional<MoveInformation>>>(Arrays.asList(() -> firstStep(), () -> secondStep()));
    }

    @NotNull
    @Override
    public Hanoi getHanoi() {
        return hanoi;
    }

    private class HanoiWalshParameter {
        public Hanoi.TowerID towerIDHavingSmallestDisk;
        public Hanoi.TowerID towerIDHavingEvenDisk;
        public Hanoi.TowerID towerIDOfSecondTower;
        public Hanoi.TowerID towerIDOfOtherTower;

        public HanoiWalshParameter(Hanoi.TowerID towerIDHavingSmallestDisk, Hanoi.TowerID towerIDHavingEvenDisk, Hanoi.TowerID towerIDOfSecondTower, Hanoi.TowerID towerIDOfOtherTower) {
            this.towerIDHavingSmallestDisk = towerIDHavingSmallestDisk;
            this.towerIDHavingEvenDisk = towerIDHavingEvenDisk;
            this.towerIDOfSecondTower = towerIDOfSecondTower;
            this.towerIDOfOtherTower = towerIDOfOtherTower;
        }

        public HanoiWalshParameter() {
        }
    }
}
