package utils;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;

/**
 * Created by shuang.xiang on 2016/4/20.
 */
public class Utils {

    /**
     * Fragment跳转， 将一个layout替换为新的fragment。
     *
     * @param fm
     * @param replaceLayoutId
     * @param fragmentClass
     * @return
     */
    public static Fragment replace(FragmentManager fm, int replaceLayoutId, Class<? extends Fragment> fragmentClass) {
        return replace(fm, fragmentClass, replaceLayoutId, fragmentClass.getSimpleName(), null);
    }
    /**
     * Fragment跳转， 将一个layout替换为新的fragment。
     *
     * @param fm
     * @param fragmentClass
     * @param tag
     * @param args
     * @return
     */
    public static Fragment replace(FragmentManager fm, Class<? extends Fragment> fragmentClass, int replaceLayoutId, String tag,
                                   Bundle args) {
        // mIsCanEixt = false;
        Fragment fragment = fm.findFragmentByTag(tag);
        boolean isFragmentExist = true;
        if (fragment == null) {
            try {
                isFragmentExist = false;
                fragment = fragmentClass.newInstance();
                if (args != null)
                    fragment.setArguments(args);
                else {
                    fragment.setArguments(new Bundle());
                }

            } catch (InstantiationException e) {
                e.printStackTrace();
            } catch (IllegalAccessException e) {
                e.printStackTrace();
            }
        } else {
            if (args != null) {
                if (fragment.getArguments() != null)
                    fragment.getArguments().putAll(args);
                else
                    fragment.setArguments(args);
            }
        }
        if (fragment == null)
            return null;
        if (fragment.isAdded()) {
            // fragment.onResume();
            return fragment;
        }
        FragmentTransaction ft = fm.beginTransaction();
        if (isFragmentExist) {
            ft.replace(replaceLayoutId, fragment);
        } else {
            ft.replace(replaceLayoutId, fragment, tag);
        }

        ft.addToBackStack(tag);
        ft.commitAllowingStateLoss();
        return fragment;
    }
}
